#include <Arduino.h>
#include <WiFiManager.h>
#include <U8g2lib.h>


WiFiManager wifiManager;
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2
(U8G2_R0, /*clock=*/14, /*data=*/12, U8X8_PIN_NONE);

void setupWiFi();
void displayStatus(const char* message, bool isConnected = false);

void setup() {
    Serial.begin(115200);

    u8g2.begin();
    u8g2.clearBuffer();
    displayStatus("Connecting");

    setupWiFi(); // Connect to Wi-Fi on startup
}

void loop() {
    delay(100); // Keep loop to avoid rapid cycling
}

void setupWiFi() {
    Serial.println("Attempting to connect to WiFi...");
    bool res = wifiManager.autoConnect("ESP-ESTUFA");

    if (!res) {
        Serial.println("Connection failed. Restarting...");
        displayStatus("Status: Not Connected");
        delay(3000); // Allow time to read the failure message
    } else {
        Serial.println("Connected to WiFi!");
        displayStatus("Status: Connected", true);
    }
}

void displayStatus(const char* message, bool isConnected) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_7x14B_tr);
    u8g2.drawStr(0, 30, message);
    u8g2.sendBuffer();
}
