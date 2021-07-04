#include "ota.hpp"
#include "serial.hpp"
#include <LittleFS.h>

void ota_setup(const char* ssid) {

  DEBUG_OUT.println("Booting");
  boolean result = WiFi.softAP(ssid);
  while (result == false) {
    DEBUG_OUT.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  DEBUG_OUT.println(WiFi.softAPIP().toString());

  // Port defaults to 3232
  //  ArduinoOTA.setPort(8266);

  // Hostname defaults to esp3232-[MAC]
  ArduinoOTA.setHostname("myesp32.local");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

    ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else{ // U_SPIFFS
      type = "filesystem";
      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      LittleFS.end();
    }
    if(DEBUG_SERIAL == false) debug_out.clear();
    DEBUG_OUT.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    DEBUG_OUT.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    DEBUG_OUT.println("Progress:" +String(progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    DEBUG_OUT.print("Error[" + String(error) + "]: ");
    if (error == OTA_AUTH_ERROR) DEBUG_OUT.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) DEBUG_OUT.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) DEBUG_OUT.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) DEBUG_OUT.println("Receive Failed");
    else if (error == OTA_END_ERROR) DEBUG_OUT.println("End Failed");
  });
  ArduinoOTA.begin();
}
