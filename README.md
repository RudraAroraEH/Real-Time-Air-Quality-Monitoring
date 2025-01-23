# Real-Time-Air-Quality-Monitoring

Overview
This project implements a Real-Time Air Quality Monitoring System that measures temperature, humidity, and air quality using a NodeMCU microcontroller and connected sensors. The data is displayed on a 0.96" OLED display and sent to the Blynk IoT platform for remote monitoring. The system also includes audible alerts through a buzzer and email notifications for poor air quality.

---

Features
- Sensors: Monitors temperature, humidity (DHT11), and air quality (MQ135 sensor).
- Display: Real-time data visualization on a 0.96" OLED screen.
- Connectivity: Sends data to the Blynk IoT platform for remote monitoring.
- Alerts: Triggers a buzzer and sends email alerts when poor air quality is detected.
- Custom Thresholds: Easily configurable thresholds for air quality alerts.

---

Components Required

1. NodeMCU (ESP8266) - Microcontroller for IoT integration
2. DHT11 Sensor - For temperature and humidity sensing
3. MQ135 Sensor - For air quality monitoring
4. 0.96" OLED Display (SSD1306) - To display real-time data
5. Buzzer - For audible alerts

---

Circuit Diagram

1. Connect the DHT11 sensor as follows:
   - VCC -> 3.3V
   - GND -> GND
   - Data -> D4 (GPIO2)

2. Connect the MQ135 sensor as follows:
   - VCC -> 3.3V
   - GND -> GND
   - Analog Out -> A0

3. Connect the OLED Display:
   - VCC -> 3.3V
   - GND -> GND
   - SDA -> D2 (GPIO4)
   - SCL -> D1 (GPIO5)

4. Connect the Buzzer:
   - Positive Terminal -> D5 (GPIO14)
   - Negative Terminal -> GND

---


Contributors
- Dhwani Shah
- Moksha Modi 

---

Feedback and Support
Feel free to open an issue or contact us via email for any questions or suggestions.

