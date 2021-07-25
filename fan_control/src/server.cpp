#include "server.hpp"
#include "collector.hpp"
#include "serial.hpp"

#include <FS.h>

static String FAN_VERSION = "1.0.1" ;

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


void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain;charset=utf-8", "Not found");
}

int week_counter = 0;
int month_counter = 0;

void server_setup(){
  LittleFS.begin();

  server.on("/weekly", HTTP_ANY, [](AsyncWebServerRequest * request) {
    DEBUG_OUT.println("weekly start");
 
    AsyncWebServerResponse *response = request->beginChunkedResponse("application/json", [](uint8_t *buffer, size_t maxLen, size_t index) -> size_t {

      if(week_counter == 2*WEEK){ // sent all data (ret 0), reset counter 
        week_counter = 0;
        DEBUG_OUT.println("weekly end");
        return 0;
      }
      String to_send = "";
      if(week_counter  == 0 ) to_send = "[[";
      else if(week_counter == WEEK) to_send = "],[";
      else to_send += ",";
      to_send += collector.week_data(week_counter);
      if(week_counter == (2*WEEK - 1)) to_send += "]]";
      week_counter++;
      //send the data, copy to buffer
      to_send.getBytes(buffer, maxLen); 
      return to_send.length();
    });
    request->send(response);
  });

  server.on("/monthly", HTTP_ANY, [](AsyncWebServerRequest * request) {
    DEBUG_OUT.println("monthly start");
 
    AsyncWebServerResponse *response = request->beginChunkedResponse("application/json", [](uint8_t *buffer, size_t maxLen, size_t index) -> size_t {

      if(month_counter == 2*MONTH){ // sent all data (ret 0), reset counter 
        month_counter = 0;
        DEBUG_OUT.println("monthly done");
        return 0;
      }
      String to_send = "";
      if(month_counter  == 0 ) to_send = "[[";
      else if(month_counter == MONTH) to_send = "],[";
      else to_send += ",";
      // getting the acual data, just one point at a time (for simplicity, hope speed is ok)
      to_send += collector.month_data(month_counter);
      if(month_counter == (2*MONTH - 1)) to_send += "]]";
      month_counter++;
      //send the data, copy to buffer
      to_send.getBytes(buffer, maxLen); 
      return to_send.length();
    });
    request->send(response);
  });

  server.on("/log", HTTP_ANY, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginChunkedResponse("text/html", [](uint8_t *buffer, size_t maxLen, size_t index) -> size_t {
      if(debug_out.empty()) return 0;
      String to_send = String();
      to_send.reserve(maxLen);
      while(!debug_out.empty()){
        String add_next = debug_out.first();
        if( (add_next.length() + 5 + to_send.length() ) > maxLen ) break ; // dont overflow buffer
        to_send.concat(add_next);
        to_send.concat("<br/>");
        debug_out.pop();
      }
      to_send.getBytes(buffer, maxLen);
      return to_send.length();
    });
    request->send(response);
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    DEBUG_OUT.println("Index.html "  + FAN_VERSION);
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
