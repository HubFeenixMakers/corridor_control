#include "server.hpp"
#include "collector.hpp"
#include "serial.hpp"

#include <FS.h>

#define DEBUG_OUT Serial

String getContentType(String filename){
  if(filename.indexOf(".htm") > 0) return "text/html";
  else if(filename.indexOf(".html")> 0) return "text/html";
  else if(filename.indexOf(".css")> 0) return "text/css";
  else if(filename.indexOf(".js")> 0) return "application/javascript";
  else if(filename.indexOf(".png")> 0) return "image/png";
  else if(filename.indexOf(".gif")> 0) return "image/gif";
  else if(filename.indexOf(".jpg")> 0) return "image/jpeg";
  else if(filename.indexOf(".ico")> 0) return "image/x-icon";
  else if(filename.indexOf(".xml")> 0) return "text/xml";
  else if(filename.indexOf(".pdf")> 0) return "application/x-pdf";
  return "text/plain";
}



// AsyncCallbackJsonWebHandler* monthly = new AsyncCallbackJsonWebHandler("/monthly");
//  monthly.onRequest( [](AsyncWebServerRequest *request, JsonVariant &json) {
//   const JsonArray& root_array = json.as<JsonArray>();
//   JsonArray nested = root_array.createNestedArray();
//   copyArray(collector.month_in , MONTH , nested);
//   nested = root_array.createNestedArray();
//   copyArray(collector.month_out , MONTH , nested);
// });

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain;charset=utf-8", "Not found");
}

void server_setup(){
  LittleFS.begin();

  server.on("/weekly", HTTP_ANY, [](AsyncWebServerRequest * request) {
    DEBUG_OUT.println("weekly");
    String data = collector.week_data();
    request->send(200, "application/json;charset=utf-8", data);
    data.clear();
  });
  server.on("/monthly", HTTP_ANY, [](AsyncWebServerRequest * request) {
    String data = collector.month_data();
    request->send(200, "application/json;charset=utf-8", data);
    data.clear();
  });


  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    DEBUG_OUT.println("Index.html");
    request->send(LittleFS, "/index.html", "text/html;charset=utf-8");
  });
  server.on("/chartist.min.css.gz", HTTP_GET, [](AsyncWebServerRequest *request){
    DEBUG_OUT.println("/chartist.min.css.gz");
    AsyncWebServerResponse *response = request->beginResponse(LittleFS, "/chartist.min.css.gz", "text/css;charset=utf-8");
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  server.on("/chartist.min.js.gz", HTTP_GET, [](AsyncWebServerRequest *request){
    DEBUG_OUT.println("/chartist.min.js.gz");
    AsyncWebServerResponse *response = request->beginResponse(LittleFS, "/chartist.min.js.gz", "application/javascript;charset=utf-8");
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
    DEBUG_OUT.println("/favicon.ico");
    request->send(LittleFS, "/favicon.ico", "image/x-icon");
  });

	DEBUG_OUT.println("HTTP server started");

  server.onNotFound(notFound);

  server.begin();
}

void server_loop() {

}
