# Smart Irrigation System with Real-Time Soil & Water Level Monitoring (Arduino)

An automatic irrigation system that monitors soil moisture, temperature, humidity, and water tank level to intelligently control a water pump. The system ensures efficient water usage, prevents dry running of the pump, and provides real-time visual and audio feedback.

---

## Features
- Real-time temperature and humidity monitoring using DHT22
- Soil moisture sensing with calibrated percentage output
- Water tank level monitoring using ultrasonic sensor
- Automatic pump control based on soil condition
- Pump dry-run protection
- OLED display for live system status
- Buzzer alerts for soil condition changes
- LED indication for low water level
- Serial monitor output for debugging

---

## System Working
1. The system initializes all sensors and output devices.
2. Soil moisture, temperature, humidity, and tank level are read continuously.
3. Raw sensor values are processed and converted into usable units.
4. Soil moisture is compared with a predefined threshold.
5. Water availability in the tank is verified.
6. The pump is turned ON or OFF automatically.
7. System status is displayed on the OLED.
8. Buzzer and LED provide user alerts.
9. The process repeats continuously.

---

## Hardware Components
- Arduino Uno
- Soil Moisture Sensor
- DHT22 Temperature and Humidity Sensor
- Ultrasonic Sensor (HC-SR04)
- Relay Module (Active-Low)
- Water Pump
- OLED Display (128×64, I2C)
- Buzzer
- LED
- Jumper Wires
- Breadboard

---

## Pin Configuration

| Component | Arduino Pin |
|----------|-------------|
| Soil Moisture Sensor | A0 |
| DHT22 Data | D7 |
| Relay (Pump) | D13 |
| Ultrasonic Trigger | D8 |
| Ultrasonic Echo | D9 |
| Buzzer | D6 |
| LED | D5 |
| OLED SDA | A4 |
| OLED SCL | A5 |

---

## Software Requirements
- Arduino IDE
- Required Libraries:
  - Adafruit GFX Library
  - Adafruit SSD1306 Library
  - DHT Sensor Library
  - Wire Library

---

## Flowchart Summary
Start → Initialize System → Read Sensors → Process Data → Check Conditions → Control Pump → Display Status → Repeat

---

## Safety and Reliability
- Pump operation is disabled when the water tank is empty.
- Sensor error handling prevents invalid readings.
- State-based control avoids repeated buzzer activation.

---

## Applications
- Smart agriculture
- Home gardening
- Greenhouses
- Water conservation systems
- Precision irrigation

---

## Limitations
- No internet connectivity (offline system)
- Manual calibration required for different soil types
- Not suitable for large-scale farms without enhancements

---

## Future Enhancements
- IoT and mobile application integration
- Weather-based irrigation control
- Data logging and analytics
- Solar-powered system
- Remote notifications

---

## License
This project is open-source and free to use for educational purposes.

---

## Author
Suayush Kumar Das  
Final Year B.Tech (Electronics and Communication Engineering)

---

If you find this project useful, please consider starring the repository.
