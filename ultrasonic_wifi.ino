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
