#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

static AsyncWebServer server(80);

void server_setup();
void server_loop();
