# **Car Control (Gyro & Self-Driving)** 🔥


## Introduction 🚀
This project creates a smart car controlled either by X and Y values from an MPU6050 gyroscope, or self-driving.
1. The gyroscope is connected to an Arduino Uno, which sends the data to a laptop for processing. The laptop forwards the data to an ESP8266 via Wi-Fi, and the ESP8266 controls the car's DC motors through an L298N motor driver. This project explores wireless communication, IoT, and real-time motor control.
2. self-driving and avoiding obstacles using Ultrasonic.

---

## Hardware Components 🛠
1. Arduino Uno: Microcontroller used to read sensor data.
2. MPU6050 Gyroscope: Provides X and Y values.
3. ESP8266: Wi-Fi module used to control motors.
4. L298N Motor Driver: Controls the DC motors.
5. DC Motors: Used to drive the car.
6. Ultrasonic

---

## Software and Libraries 💻
- Arduino IDE: To program the Arduino and ESP8266.
- Python : To process gyro data and communicate with the ESP8266.
### Libraries:
- Arduino: [wire.h]( https://www.arduino.cc/reference/en/libraries/wire/), [ESP8266WiFi.h](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/ESP8266WiFi.h), [ESP8266WebServer.h](https://arduino-esp8266.readthedocs.io/en/latest/esp8266webserver/readme.html), [ArduinoJson.h](https://arduinojson.org/), [QMC5883LCompass.h](https://github.com/mprograms/QMC5883LCompass).
- Python: [cvzone](https://pypi.org/project/cvzone/), [requests](https://docs.python-requests.org/en/latest/), [json](https://docs.python.org/3/library/json.html).

---

## System Architecture and Algorithm 🧠

### mode 1 : using gyro
### 1. MPU6050 → Arduino
- The MPU6050 gyroscope is connected to the Arduino Uno via I2C. The Arduino reads gyro values (X and Y axes) and transmits them to the laptop via a serial interface using the cvzone library.

### 2. Arduino → Laptop
- The laptop reads the gyro values from the Arduino using cvzone. These values are processed, scaled, and adjusted for calibration.

### 3. Laptop → ESP8266
- The laptop sends the processed data to the ESP8266 using an HTTP POST request over Wi-Fi. The ESP8266 receives the data and sends commands to the L298N motor driver to control the car's movement.

### 4. ESP8266 → Motor Driver
- The L298N motor driver controls the DC motors based on the orientation data received from the ESP8266 and the speed will changed according to its values.

### mode 2 : using ultrasonic

- the ulttasonic sensor reads the distance and controls the motors according to it.

---

## How it Works  ⁉️

### Hardware Setup
- Connect the MPU6050 to the Arduino Uno via I2C.
- Connect the ESP8266 to the Arduino.
- Connect the L298N motor driver to the DC motors and ESP8266 pins.

### Software Setup
- Install the required libraries in the Arduino IDE.

### Usage

- Upload the Arduino code to the Arduino Uno.
- Run the Python code to process the gyro data and send it to the ESP8266.
- choose the mode.
- mode 1 : Control the car's movement by tilting the sensor or using a smartphone gyroscope.
- mode 2 : the car will drive by itself.

---

## Code Explanation 📝

### Arduino Code
- MPU6050 Data Reading: Reads X and Y values from the gyro.
- Data Transmission: Sends the data to the laptop via serial communication.
### Python Code
- Gyro Data Processing: Receives and adjusts gyro data using cvzone.
- Wi-Fi Communication: Sends the processed data to the ESP8266 using HTTP POST requests.
### ESP8266 Code
- Wi-Fi Setup: Connects to Wi-Fi and hosts a web server.
- Motor Control: Controls DC motor directions based on gyro values or self-driving.

---


## Future Improvements 👀
 
- Replace the laptop with direct communication between Arduino and ESP8266.
- Implement traffic signal recognition using machine learning.

---

## Resources 📌

- [ESP8266 Documentation](https://docs.espressif.com)
- [Random Nerd Tutorials](https://randomnerdtutorials.com)
