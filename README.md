# Smart-Automatic-Irrigation-System-Using-Arduino
Smart Irrigation System with Real-Time Soil & Water Level Monitoring (Arduino)

An automatic irrigation system that monitors soil moisture, temperature, humidity, and water tank level to intelligently control a water pump.
The system ensures efficient water usage, prevents dry running of the pump, and provides real-time visual and audio feedback.

📌 Features

🌡️ Real-time Temperature & Humidity monitoring (DHT22)

🌱 Soil moisture sensing with percentage calibration

🚰 Water tank level monitoring using ultrasonic sensor

🔁 Automatic pump control based on soil condition

🛑 Pump dry-run protection

🖥️ OLED display for live system status

🔊 Buzzer alerts for soil condition changes

💡 LED indication for low water level

📟 Serial monitor output for debugging

🧠 System Working

System initializes all sensors and modules.

Reads soil moisture, temperature, humidity, and tank level.

Converts raw sensor values into usable units.

Checks if soil moisture is below the defined threshold.

Verifies water availability in the tank.

Automatically turns the pump ON/OFF.

Displays real-time data on OLED.

Alerts user through buzzer and LED.

Repeats the process continuously.

🔧 Hardware Components

Arduino Uno

Soil Moisture Sensor

DHT22 Temperature & Humidity Sensor

Ultrasonic Sensor (HC-SR04)

Relay Module (Active-Low)

Water Pump

OLED Display (128×64, I2C)

Buzzer

LED

Jumper Wires & Breadboard
