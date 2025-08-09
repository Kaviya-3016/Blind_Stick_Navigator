# Blind_Stick_Navigator
# Blind Stick Navigator (IoT-Based)

![Project Thumbnail](project-thumbnail.png)

An **IoT-enabled assistive device** designed for visually impaired individuals.  
It uses an **HC-SR04 ultrasonic sensor** to detect obstacles, a **buzzer** for audio alerts, and **Wi-Fi** for real-time data transmission to the **Thingzmate IoT Cloud**.

---

## 📌 Features
- Detects obstacles within **10 cm** using ultrasonic sensor
- Provides **audio alert** via buzzer
- Sends **real-time JSON data** to Thingzmate IoT Cloud
- Wi-Fi based **wireless communication**
- Can be monitored remotely

---

## 🛠 Hardware Used
- **ESP32 Dev Board**
- **HC-SR04 Ultrasonic Sensor**
- **Buzzer**
- USB Cable for power
- Wi-Fi Network

---

## ⚡ Circuit Diagram
![Circuit Diagram](circuit-diagram.png)

| ESP32 Pin | Component         | Pin Name |
|-----------|-------------------|----------|
| 27        | Ultrasonic Sensor | TRIG     |
| 15        | Ultrasonic Sensor | ECHO     |
| 26        | Buzzer            | Signal   |
| 3V3       | Ultrasonic Sensor | VCC      |
| 3V3       | Buzzer            | VCC      |
| GND       | Ultrasonic Sensor | GND      |
| GND       | Buzzer            | GND      |

---

## 💻 Setup Instructions
1. Install the **Arduino IDE** and ESP32 board package.
2. Install required libraries:
   - `WiFi.h`
   - `HTTPClient.h`
3. Connect hardware as per the circuit diagram.
4. Update in the code:
   - `WIFI_SSID` and `WIFI_PASSWORD` with your network credentials.
   - `serverUrl` and `AuthorizationToken` with your Thingzmate credentials.
5. Upload the code to the ESP32 board.

---

## 📤 JSON Data Sent
Example payload:
```json
{
  "distance_cm": 5.42,
  "object_detected": true
}
