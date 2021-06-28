#include <Arduino.h>

#include "ota.hpp"
#include "server.hpp"
#include "collector.hpp"
#include "serial.hpp"


const char* ssid = "fan_XXX";

void setup() {
  DEBUG_OUT.begin(115200);
  ota_setup(ssid);
  server_setup();
  DEBUG_OUT.println(F("Setup done"));
  DEBUG_OUT.print("IP address: ");
  DEBUG_OUT.println(WiFi.softAPIP());
}

void loop() {
  ArduinoOTA.handle();
	server_loop();
  collector_loop();
}
