#include <Arduino.h>
#include <led.h>

void setup()
{
  Serial.begin(115200);
  delay(1000); // Give time for serial monitor to connect
}

void loop()
{
  // put your main code here, to run repeatedly:
  turnLEDGreen(LED_BUILTIN); // Toggle LED
  delay(500);
  turnLEDBlue(LED_BUILTIN); // Toggle LED
  delay(500);
}