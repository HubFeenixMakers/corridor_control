#include <Arduino.h>

#include "ota.hpp"

// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


// mini https://chewett.co.uk/blog/1066/pin-numbering-for-wemos-d1-mini-esp8266/
DHT dht_in(4, DHT11);  // D2 on mini
DHT dht_out(5, DHT11); // D1 on mini

// Set delay between sensor readings based on sensor details.
uint32_t delayMS = 3000 ;

const char* ssid = "fan_XXX";

void setup() {
  Serial.begin(115200);
  ota_setup(ssid);
  Serial.println(WiFi.softAPIP());


  // Initialize device.
  dht_in.begin();
  dht_out.begin();
  Serial.println(F("DHT set up"));
}

void loop() {
  ArduinoOTA.handle();

  // Delay between measurements.
  delay(delayMS);

  // Get temperature event and print its value.
  Serial.print(F("Temperature inside: "));
  Serial.print(dht_in.readTemperature());
  Serial.println(F("°C"));
  Serial.print(F("Temperature outside: "));
  Serial.print(dht_out.readTemperature());
  Serial.println("°C");
}
