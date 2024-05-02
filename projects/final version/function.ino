#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <BH1750.h>
#include <PDM.h>
#include "smart_light_bulb_inferencing.h"

#define NEOPIXEL_PIN    A6       // Define the pin where the NeoPixel is connected
#define NUMPIXELS       8        // Number of LEDs in the NeoPixel strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRBW + NEO_KHZ800);
BH1750 lightMeter;

typedef struct {
    signed short *buffers[2];
    unsigned char buf_select;
    unsigned char buf_ready;
    unsigned int buf_count;
    unsigned int n_samples;
} inference_t;

static inference_t inference;
static bool record_ready = false;
static signed short *sampleBuffer;
static bool debug_nn = false; // Set this to true to see e.g. features generated from the raw signal
static int print_results = -(EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW);

void setup() {
    Serial.begin(115200);
    while (!Serial); // Wait for USB connection to be established
    Serial.println("Edge Impulse Inferencing Demo");

    // Initialize NeoPixel strip
    pixels.begin();
    pixels.setBrightness(255);
    pixels.show();

    // Initialize BH1750 light sensor
    if (!lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
        Serial.println("Could not find a valid BH1750 sensor, check wiring!");
    }

    // Setup PDM microphone
    run_classifier_init();
    if (!microphone_inference_start(EI_CLASSIFIER_SLICE_SIZE)) {
        Serial.println("Failed to allocate audio buffer for microphone inference");
        return;
    }
}

void loop() {
    if (!microphone_inference_record()) {
        Serial.println("Failed to record audio");
        return;
    }

    signal_t signal = { EI_CLASSIFIER_SLICE_SIZE, &microphone_audio_signal_get_data };
    ei_impulse_result_t result = {0};

    if (run_classifier_continuous(&signal, &result, debug_nn) != EI_IMPULSE_OK) {
        Serial.println("Failed to run classifier");
        return;
    }

    if (++print_results >= (EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW)) {
        handle_result(result);
        print_results = 0;
    }
}

void handle_result(ei_impulse_result_t result) {
    // Print classification results
    Serial.println("Predictions (DSP, Classification, Anomaly):");
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        Serial.print(result.classification[ix].label);
        Serial.print(": ");
        Serial.println(result.classification[ix].value, 6);
    }

    // Determine the command with the highest confidence
    const char* command = result.classification[0].label;
    float max_value = result.classification[0].value;

    for (size_t ix = 1; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        if (result.classification[ix].value > max_value) {
            max_value = result.classification[ix].value;
            command = result.classification[ix].label;
        }
    }

    // Perform actions based on the command
    float currentLux = lightMeter.readLightLevel();
    int brightness = map(currentLux, 0, 1000, 255, 10);
    brightness = constrain(brightness, 10, 255);

    if (strcmp(command, "link") == 0) {
        setAllPixels(255, 223, 191, brightness); // Warm white with varying brightness
    } else if (strcmp(command, "cut") == 0) {
        setAllPixels(255, 223, 191, 0); // Turn off all LEDs
    } else if (strcmp(command, "breathe") == 0) {
        breatheEffect(255, 223, 191, brightness); // Breathing effect with varying brightness
    }
}

void setAllPixels(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness) {
    pixels.setBrightness(brightness);
    for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(red, green, blue));
    }
    pixels.show();
}

void breatheEffect(uint8_t red, uint8_t green, uint8_t blue, uint8_t baseBrightness) {
    for (int i = 0; i < 256; i++) { // Fade in
        int breathBrightness = baseBrightness * (i / 255.0);
        setAllPixels(red, green, blue, breathBrightness);
        delay(5);
    }
    for (int i = 255; i >= 0; i--) { // Fade out
        int breathBrightness = baseBrightness * (i / 255.0);
        setAllPixels(red, green, blue, breathBrightness);
        delay(5);
    }
}
