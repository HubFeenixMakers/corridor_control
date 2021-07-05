#include <Arduino.h>

#include "ota.hpp"
#include "server.hpp"
#include "collector.hpp"
#include "serial.hpp"



void setup() {
  Serial.begin(115200);
  ota_setup();
  server_setup();
  collector_setup();
  DEBUG_OUT.println(F("Setup done"));
  DEBUG_OUT.println(String("IP address: ") + WiFi.softAPIP().toString());
}

void loop() {
  ArduinoOTA.handle();
	server_loop();
	collector_loop();
}
