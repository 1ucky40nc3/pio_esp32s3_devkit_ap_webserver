#include <Arduino.h>
#include <WiFi.h>
#include <led.h>
#include <config.h>
#include <secrets.h>

void setup()
{
  Serial.begin(SERIAL_BAUD);
  delay(DELAY_AFTER_SERIAL_INITIALIZED); // Give time for serial monitor to connect

  // Set the Wi-Fi mode to Access Point
  WiFi.mode(WIFI_AP);

  // Start the AP with the specified SSID and password
  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);

  // Print the details
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("AP SSID: ");
  Serial.println(WIFI_SSID);
}

void loop()
{
  // put your main code here, to run repeatedly:
  turnLEDGreen(LED_BUILTIN); // Toggle LED
  delay(500);
  turnLEDBlue(LED_BUILTIN); // Toggle LED
  delay(500);
}