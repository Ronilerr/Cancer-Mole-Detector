Cancer Mole Detector
This project is an IoT-based smart skin health monitoring system that detects and classifies skin lesions (such as moles) using computer vision and a trained machine learning model. It integrates an ESP32-CAM module, Python-based Flask server, and a convolutional neural network (CNN) to provide real-time feedback to the user.

Features
Captures images of skin lesions using ESP32-CAM

Sends images to a local Flask server for analysis

Classifies lesions using a pre-trained CNN model

Displays results via Blynk IoT mobile application

Provides audio feedback and mock email notification

Folder Structure
Model.py: Defines the CNN architecture.

Train.py: Handles training of the CNN model.

datagenerator.py: Generates training and validation datasets.

run_model.py: Loads the trained model and makes predictions.

main.py: Coordinates the overall application logic.

server.py: Flask server that receives image uploads and serves predictions.

Selector.py: Helper script for selecting images.

pixels.py: Preprocessing utilities.

SkinScan_Notifier.ino: Arduino code for ESP32 to take photos and connect to the Flask server.

models/skin_lesion_classifier.h5: The saved trained model.

predictions.json: Stores recent prediction results.

Requirements
Python
Python 3.7+

Flask

TensorFlow / Keras

NumPy

Pillow


Arduino
ESP32 board package

Blynk library

Arduino IDE or PlatformIO

How It Works
The ESP32-CAM captures an image and uploads it to a local server.

The Flask server preprocesses the image and runs inference using the trained CNN model.

The result is saved in predictions.json.

The ESP32 retrieves the classification result via HTTP.

The classification is displayed in Blynk and spoken via a buzzer/speaker.

A fake email notification is generated for demo purposes.

Getting Started
Train your model using Train.py or use the provided model in the models directory.

Run the Flask server:

bash
Copy
Edit
python server.py
Flash the SkinScan_Notifier.ino to the ESP32-CAM using the Arduino IDE.

Connect the device to WiFi and test image capture.

Use the Blynk app to view predictions.

Notes
This project is for educational and demo purposes only.

The model should not be used for real medical diagnosis.

A good dataset to use for training is the ISIC 2019 Skin Lesion dataset.

License
This project is provided under the MIT License.
