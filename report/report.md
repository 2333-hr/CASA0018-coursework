# Smart Voice Light: A Voice-Activated Lighting System

Huarui Yang

link to github:[https://github.com/2333-hr/CASA0018-coursework](https://github.com/2333-hr/CASA0018-coursework)

link to Edge Impulse projects:[https://studio.edgeimpulse.com/studio/362703](https://studio.edgeimpulse.com/studio/362703)

## Introduction
### Project Overview

The "Smart Voice Light" project is a sophisticated lighting system activated and controlled through voice commands. It leverages a voice recognition model to interpret spoken instructions like "link," "cut," and "breathe," each triggering specific lighting responses. By integrating advanced machine learning algorithms with practical hardware components, the system allows users to manage lighting atmospheres hands-free.

![4bc4a68a23f8cdc26534121b72e53eb](https://github.com/2333-hr/CASA0018-coursework/assets/146243657/75cca286-e05e-4a28-9992-5c24aa5f8c82)

### Inspiration

The inspiration behind this project stemmed from the growing demand for smart home technologies that enhance convenience and accessibility. In scenarios where manual interaction with devices is impractical or undesirable—such as cooking in the kitchen or when returning home with hands full—the ability to control lighting through voice can significantly enhance user experience and safety.

### Examples and Basis

The project draws on existing voice smart control products from products such as Amazon Echo , Google Home , Amazon Echo and Google Home as well as voice control that references various smart home features. However, unlike these products that rely on commercial cloud services, the "smart voice light" hardware runs entirely on local hardware. This approach ensures faster response times and protects user privacy. Furthermore, this project reflects a setup for real-time audio processing in embedded system design, making it a practical example of applying machine learning in an IoT environment.

![image](https://github.com/2333-hr/CASA0018-coursework/assets/146243657/1bc92bd1-e1ec-4d5a-98d4-9880fc78c4ca)

## Research Question
Objective: How can voice recognition technology be effectively utilized to control lighting systems in a responsive and user-friendly manner?

## Application Overview
### System Architecture
The "Smart Voice Light" project is designed around a robust wooden housing crafted via laser cutting, which encloses the system’s core electronics. The central components include an Arduino Nano 33 BLE Sense, equipped with an onboard microphone for audio input, a BH1750 light intensity sensor to adjust LED brightness automatically, and a NeoPixel LED strip that serves as the visual output. This combination allows for an intelligent lighting system that responds dynamically to both vocal commands and ambient light conditions.

### Data Flow and Interaction:
Voice commands are captured live through the Arduino’s microphone and then analyzed by a machine learning model, previously trained and deployed via the Edge Impulse platform. Depending on the recognized command—be it "link," "cut," or "breathe"—the system adjusts the LED strip accordingly. The "link" command lights up the LED strip to full brightness, which adjusts in real-time based on the readings from the BH1750 sensor, ensuring optimal lighting conditions. The "cut" command turns off the LEDs, while the "breathe" effect causes them to gently pulse, creating a calming ambiance. This setup not only offers convenience and efficiency but also enhances user interaction with their environment.

*Tip: probably ~200 words and a diagram is usually good to convey your design!*

## Data

In the development of the Smart Voice Light project, we utilized a variety of audio data sourced from ambient environments and self-recordings to train our machine learning model, ensuring the robustness and versatility of the voice command recognition. The data collection involved gathering audio samples from various individuals in different settings to capture a diverse array of acoustic scenarios, including specific 'background' or silence samples. These background samples play a crucial role in training the model to distinguish between deliberate commands and inadvertent noises or silence, significantly reducing the likelihood of false activations.

To prepare the data for training, it underwent several preprocessing steps. Initially, all audio samples were normalized to maintain consistency in volume and clarity across the dataset. Subsequent to normalization, we employed techniques like trimming silence and filtering background noise to refine the quality of the training data, ensuring that even subtle variations in sound are accurately captured without interference from ambient noise. The cleaned samples were then labeled accurately to correspond with the respective commands they represent—'link', 'cut', 'breathe', and 'background', forming a structured dataset that was split into training and testing sets. This balance prevents overfitting and optimizes model performance.

The Edge Impulse platform was instrumental in visualizing and configuring the data, enabling us to tweak parameters such as Mel Frequency Cepstral Coefficients (MFCCs) settings, which are critical for capturing the essence of sound in model training. The detailed analysis and configuration tools provided by the platform allowed for a meticulous approach to model tuning and performance enhancement, ensuring each voice command—and the crucial non-commands represented by 'background'—triggers the appropriate response in our smart light application.

![image](https://github.com/2333-hr/CASA0018-coursework/assets/146243657/9b404fcd-bd55-4e0c-b778-ef039cfce712)

## Model


## Experiments
First, after the model training is completed, I test the accuracy of my model through the test page provided by Inpulse Edge (including web and mobile). After deploying the model on ARDUINO NANO 33 BLE, I also tested the project through the output of the onboard microphone on the serial monitor. I actually had multiple iterations of my model. During the iteration, in addition to increasing the number of samples, I also adjusted some model parameters. Firstly, I adjusted the window size during MFCC audio processing to cover my longest keyword length, and secondly, I adjusted the window increase parameter to ensure that the keywords are not split between the two windows, but also long enough to avoid data Too much overlap leads to increased processing burden. In addition, I also adjusted and manually added silent areas to try to ensure the accuracy of sampling. In addition to these, I have also changed the training parameters, including the number of iterations and learning rate, the number of iterations, the Dropout rate in the Neural network architecture, and the model complexity. Try a smaller learning rate, which may help the model converge more stably during training. Consider using a higher dropout rate to reduce the risk of overfitting. At the same time, because my sample data is limited, an overly complex model may lead to overfitting, so I also tried to simplify the model and finally trained the final model version.

During the experiment, I will use a fixed number of tests for a single word to test on different devices to measure the performance of the model. At the same time, I also used the onboard microphone code to run on the ARDUINO board to measure model performance through the serial monitor. In addition to this, I also used the model testing and performance calibration functions in Impulse egde to measure the functionality of the model through internal data testing.



## Results and Observations
Our project aimed at implementing a smart voice-controlled lighting system exhibited promising results upon deployment on computer and mobile platforms. However, significant performance degradation was noted when deployed on the Arduino Nano 33 BLE Sense board with the onboard microphone.

### Recognition Performance
Recognition accuracy noticeably declined on the Arduino Nano 33 BLE Sense board, requiring louder audio input for successful recognition. This discrepancy may be attributed to limitations in the onboard microphone's sensitivity and the processing power of the microcontroller.

### Background Noise Recognition
Interestingly, while background noise recognition was minimal, it proved effective in preventing erroneous recognitions. However, this suggests a need for further improvement in distinguishing between signal and noise, possibly through advanced noise filtering techniques.

### MFCC Processing Issues
MFCC processing introduced occasional audio fragments containing silence or chaotic noise, contributing to recognition errors. These issues could stem from inadequacies in the MFCC feature extraction process, particularly in handling noisy or incomplete audio samples.

### Hardware Deployment Impact
Deployment within a wooden enclosure likely hindered sound transmission, exacerbating recognition challenges. This highlights the importance of optimizing hardware placement to minimize signal attenuation and maximize microphone sensitivity.

### Overall Assessment
While the project achieved satisfactory performance on conventional platforms, challenges arose upon deployment on the Arduino Nano 33 BLE Sense board. These challenges underscore the importance of considering hardware limitations and environmental factors in system design.

### Future Directions
Moving forward, addressing the identified issues requires a multi-faceted approach. This includes exploring alternative feature extraction methods tailored to the Arduino Nano 33 BLE Sense's capabilities, implementing robust noise filtering algorithms, and optimizing hardware placement for improved signal reception. Additionally, leveraging machine learning techniques for adaptive model training could enhance recognition accuracy in diverse environments. By addressing these aspects, we aim to enhance the system's robustness and reliability across various deployment scenarios.

![image](https://github.com/2333-hr/CASA0018-coursework/assets/146243657/feb43d32-6598-4e1e-8c91-a30fbe6e8670)
![image](https://github.com/2333-hr/CASA0018-coursework/assets/146243657/cf727f49-16aa-49f0-9691-ebbfe2ddcc2c)
![image](https://github.com/2333-hr/CASA0018-coursework/assets/146243657/b4345039-ec60-428e-a5e9-9382b1884ee6)
<img width="465" alt="f8e5db370964bfa074e86f9b3b73993" src="https://github.com/2333-hr/CASA0018-coursework/assets/146243657/2d20b941-0e03-4ccf-89ea-b94709fd550c">
<img width="473" alt="5acae144959fe3ab14a69faff46f43f" src="https://github.com/2333-hr/CASA0018-coursework/assets/146243657/c99cc766-c3b7-47b0-9232-9e45cac463b1">
<img width="426" alt="710ef57d5fd6b1196d29dadeb27cb84" src="https://github.com/2333-hr/CASA0018-coursework/assets/146243657/d52a2fee-2902-4623-a6e7-5664b2a71c85">
![image](https://github.com/2333-hr/CASA0018-coursework/assets/146243657/0a37ba33-b544-4260-b6a6-f93d4a9b75ef)
![image](https://github.com/2333-hr/CASA0018-coursework/assets/146243657/5feb490b-dd87-40eb-89f9-bbf2b8fb965f)
![image](https://github.com/2333-hr/CASA0018-coursework/assets/146243657/2806d692-1316-4f3b-87eb-0d7fdff33627)

## Bibliography
*If you added any references then add them in here using this format:*

1. Last name, First initial. (Year published). Title. Edition. (Only include the edition if it is not the first edition) City published: Publisher, Page(s). http://google.com

2. Last name, First initial. (Year published). Title. Edition. (Only include the edition if it is not the first edition) City published: Publisher, Page(s). http://google.com

*Tip: we use [https://www.citethisforme.com](https://www.citethisforme.com) to make this task even easier.* 

## Declaration of Authorship

I, Huarui Yang, confirm that the work presented in this assessment is my own. Where information has been derived from other sources, I confirm that this has been indicated in the work.

Huarui Yang

2 May 2024

Word count: 
