#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <led.h>
#include <config.h>
#include <secrets.h>

WebServer server(80);

void handleRoot()
{
  server.send(200, "text/html", "<h1>Hello from your ESP32!</h1>");
  Serial.println("Handle root");
}

void handleLedGreenGet()
{
  StaticJsonDocument<200> doc;
  doc["ledState"] = "green";

  String jsonOutput;
  serializeJson(doc, jsonOutput);
  turnLEDGreen(LED_PIN);
  server.send(200, "application/json", jsonOutput);
  Serial.println("Handle LED green GET");
}

void handleLedOffGet()
{
  StaticJsonDocument<200> doc;
  doc["ledState"] = "off";

  String jsonOutput;
  serializeJson(doc, jsonOutput);
  turnLEDOff(LED_PIN);
  server.send(200, "application/json", jsonOutput);
  Serial.println("Handle LED off GET");
}

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

  server.on("/", handleRoot); // Route for the root URL
  server.on("/led/green", HTTP_GET, handleLedGreenGet);
  server.on("/led/off", HTTP_GET, handleLedOffGet);
  server.begin(); // Start the server
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
}