#include <Arduino.h>

#include "ota.hpp"
#include "server.hpp"
#include "collector.hpp"


const char* ssid = "fan_XXX";


void setup() {
  Serial.begin(115200);
  ota_setup(ssid);
  server_setup();
  Serial.println(F("Setup done"));
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  ArduinoOTA.handle();
	server_loop();
  collector_loop();
}
