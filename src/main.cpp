#include <Arduino.h>
#include <led.h>
#include <config.h>

void setup()
{
  Serial.begin(SERIAL_BAUD);
  delay(DELAY_AFTER_SERIAL_INITIALIZED); // Give time for serial monitor to connect
}

void loop()
{
  // put your main code here, to run repeatedly:
  turnLEDGreen(LED_BUILTIN); // Toggle LED
  delay(500);
  turnLEDBlue(LED_BUILTIN); // Toggle LED
  delay(500);
}