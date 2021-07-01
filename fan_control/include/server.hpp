#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncEventSource.h>
#include <LittleFS.h>

static AsyncWebServer server(80);
static AsyncEventSource events("/events");

void server_setup();
void server_loop();
