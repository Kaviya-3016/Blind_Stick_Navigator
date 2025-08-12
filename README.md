
# Blind Stick Navigator (IoT-Based)

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
- **USB Cable** for power
- **Wi-Fi** Communication Protocol

| ESP32 Pin | Component         | Pin Name |
|-----------|-------------------|----------|
| 27        | Ultrasonic Sensor | TRIG     |
| 15        | Ultrasonic Sensor | ECHO     |
| 26        | Buzzer            | Signal   |

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

```
# Source Code

```
#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials
#define WIFI_SSID "Durga"
#define WIFI_PASSWORD "passwordilla"

// Ultrasonic sensor pins
#define TRIG_PIN 27
#define ECHO_PIN 15

// Thingzmate cloud URL and Authorization token
const char *serverUrl = "https://eas.thingzmate.com/api/v1/device-types/00004/devices/0004/uplink";
String AuthorizationToken = "Bearer 668696d0daff55459c5264a295952b72";

void setup() {
  Serial.begin(115200);
  delay(3000);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
}

float getDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  if (duration == 0) {
    Serial.println("Timeout: No echo received");
    return -1.0;
  }

  float distance = duration * 0.034 / 2.0;
  return distance;
}

void loop() {
  float distance = getDistanceCM();
  bool objectDetected = false;

  if (distance <= 10 && distance > 0) {
    objectDetected = true;
    Serial.println("⚠️ Obstacle detected within 10 cm!");
  }

  Serial.print("Measured Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Prepare HTTP request to Thingzmate
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", AuthorizationToken);

  // Create JSON body
  String message = "{\"distance_cm\":" + String(distance, 2) + 
                   ",\"object_detected\":" + (objectDetected ? "true" : "false") + "}";

  Serial.println("Sending: " + message);

  int httpResponseCode = http.POST(message);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("✅ HTTP Response code: " + String(httpResponseCode));
    Serial.println("📦 Response: " + response);
  } else {
    Serial.print("❌ HTTP Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
  delay(10000);  // Send data every 10 seconds
}

```
# Serial Monitor Output
<img width="583" height="466" alt="image" src="https://github.com/user-attachments/assets/ed4c7cef-c501-446f-a5f9-b72468a08e1b" />

# Thingzmate Cloud Output

<img width="999" height="441" alt="image" src="https://github.com/user-attachments/assets/cdaa4775-6243-4370-b4cf-20e30efe9e1a" />

# 🚀 Future Enhancements
- Voice feedback for obstacle alerts.
- GPS tracking for outdoor navigation.
- Battery-powered design.
- Bluetooth low-energy support.
- AI-based obstacle classification.

# 📄 License
This project is licensed under the MIT License – see the LICENSE file for details.

---

## 👩‍💻 Author

**Kaviya Murugan, B.E. (Hons.)**  
Creator of the **Blind Stick Navigator**, combining **IoT** and **Ultrasonic Sensing** to assist visually impaired individuals with safe navigation.  
Passionate about applying **AI**, **Computer Vision**, and **IoT** for impactful real-world innovations.

🔗 **GitHub**: [Kaviya-3016](https://github.com/Kaviya-3016)  
🔗 **LinkedIn**: [Kaviya Murugan](https://www.linkedin.com/in/kaviyamurugan)

---

⭐ If you like this project, don't forget to star the repo and share it with others!

