#include <WiFi.h>
#include <HTTPClient.h>
#include <HardwareSerial.h>

// WiFi credentials
const char* ssid = "OPPO F19 PRO";
const char* password = "25817397";

// API endpoint
const char* serverName = "http://192.168.113.69:8080/api/upload-gas-data";

// Emergency service number
const char* emergencyNumber = "+918766654650";

// Pin definitions
const int gasSensorPin = 34;  // Analog pin for gas sensor (ESP32 uses 34, 35, 36, 39 for ADC)
const int buzzerPin = 25;     // Digital pin for buzzer (change as per your wiring)
const int ledPin = 33;
const int threshold = 1500;    // Threshold value for dangerous gas concentration

// GSM Module configuration (using HardwareSerial)
HardwareSerial gsmSerial(1);  // Use UART1 (TX = GPIO17, RX = GPIO16) for GSM communication

void setup() {
  Serial.begin(115200);            // Start Serial communication for debugging
  gsmSerial.begin(9600, SERIAL_8N1, 16, 17);  // RX = GPIO16, TX = GPIO17 for GSM

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Initialize gas sensor and buzzer
  pinMode(gasSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  // Read gas sensor data
  int gasValue = analogRead(gasSensorPin);  // Read analog value from the gas sensor
  Serial.println("Gas Value: " + String(gasValue));

  // Upload data to the API
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    // Prepare JSON payload
    String jsonPayload = "{\"gas_level\": " + String(gasValue) + "}";

    int httpResponseCode = http.POST(jsonPayload);
    if (httpResponseCode > 0) {
      Serial.println("Data sent to server. Response code: " + String(httpResponseCode));
    } else {
      Serial.println("Error sending data: " + String(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }

  // Trigger alerts if gas value exceeds threshold
  if (gasValue > threshold) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);  // Activate buzzer
    sendEmergencySMS(gasValue);
  } else {
    digitalWrite(buzzerPin, LOW);   // Deactivate buzzer
    digitalWrite(ledPin, LOW);
  }


  delay(5000);  // Wait for 10 seconds before next reading
}

void sendEmergencySMS(int gasValue) {
  Serial.println("Gas level critical. Sending SMS to emergency services...");
  gsmSerial.print("AT+CMGF=1\r");  // Set SMS text mode
  delay(100);
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(emergencyNumber);
  gsmSerial.println("\"\r");
  delay(100);
  gsmSerial.print("Emergency! Gas level critical: ");
  gsmSerial.print(gasValue);
  gsmSerial.println(". Immediate attention required.");
  delay(100);
  gsmSerial.write(26);  // Send Ctrl+Z to indicate end of message
  delay(1000);
  Serial.println("SMS sent.");
}
