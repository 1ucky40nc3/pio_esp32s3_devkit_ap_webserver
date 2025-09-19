#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <LittleFS.h> // Changed from <SPIFFS.h>
#include <led.h>
#include <config.h>
#include <secrets.h>

WebServer server(80);

// A new function to handle all static file requests, including the root URL.
void handleStaticFile()
{
  String path = server.uri();

  // If the path is the root URL "/", serve index.html
  if (path.endsWith("/"))
  {
    path += "index.html";
  }

  String dataType = "text/plain";
  if (path.endsWith(".html"))
  {
    dataType = "text/html";
  }
  else if (path.endsWith(".js"))
  {
    dataType = "application/javascript";
  }
  else if (path.endsWith(".css"))
  {
    dataType = "text/css";
  }
  else if (path.endsWith(".json"))
  {
    dataType = "application/json";
  }
  // Add more file types as needed

  // Check if the requested file exists in LittleFS
  if (LittleFS.exists(path))
  {
    File file = LittleFS.open(path, "r");
    server.streamFile(file, dataType);
    file.close();
  }
  else
  {
    // If the file does not exist, serve index.html as a fallback.
    // This is crucial for single-page applications like SvelteKit.
    File file = LittleFS.open("/index.html", "r");
    if (file)
    {
      server.streamFile(file, "text/html");
      file.close();
    }
    else
    {
      // If even index.html doesn't exist, send a 404 Not Found error.
      server.send(404, "text/plain", "404: Not Found");
    }
  }
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
  Serial.println("Handle LED off GET");
}

void setup()
{
  Serial.begin(SERIAL_BAUD);
  delay(DELAY_AFTER_SERIAL_INITIALIZED); // Give time for serial monitor to connect

  // Initialize LittleFS, and format if mount fails.
  if (!LittleFS.begin())
  {
    Serial.println("Mounting LittleFS failed. Attempting to format...");
    if (LittleFS.format())
    {
      Serial.println("LittleFS formatted successfully. Rebooting to remount.");
      delay(1000);
      ESP.restart();
    }
    else
    {
      Serial.println("LittleFS format failed! An error has occurred.");
      return;
    }
  }

  Serial.println("LittleFS mounted successfully.");

  // Set the Wi-Fi mode to Access Point
  WiFi.mode(WIFI_AP);

  // Start the AP with the specified SSID and password
  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);

  // Print the details
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("AP SSID: ");
  Serial.println(WIFI_SSID);

  server.on("/led/green", HTTP_GET, handleLedGreenGet);
  server.on("/led/off", HTTP_GET, handleLedOffGet);

  // Use a catch-all handler for any URI that is not specifically defined.
  // This is where all the static files will be served from.
  server.onNotFound(handleStaticFile);

  server.begin(); // Start the server
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
}
