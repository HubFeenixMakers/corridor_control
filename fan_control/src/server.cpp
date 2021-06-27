#include "server.hpp"
#include <FS.h>

#define DBG_OUTPUT_PORT Serial


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

bool handleFileRead(String path ){
  DBG_OUTPUT_PORT.println("handleFileRead: " + path);
  if(path.endsWith("/")) path += "index.html";
  String contentType = getContentType(path) + ";charset=utf-8";
  if(LittleFS.exists(path)){
    DBG_OUTPUT_PORT.println("handle: " + path);
    File file = LittleFS.open(path, "r");
    if(path.endsWith(".gz")){
      //server.sendHeader("Content-Encoding" , "gzip");
    } else {
      contentType += ";charset=utf-8";
    }
    server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

void handleHours(){

}

int LDRPin = A0;
int LDRReading = 0; 

int milisInterval = 2000;
int count = 0;

void getData() {   
   //This is a JSON formatted string that will be served. You can change the values to whatever like.
   // {"data":[{"dataValue":"1024"},{"dataValue":"23"}]} This is essentially what is will output you can add more if you like
	Serial.println("Data start");
  LDRReading = analogRead(LDRPin);
  String text2 = "{\"data\":[";
  text2 += "{\"dataValue\":\"";
  text2 += "LDRReading";
  text2 += "\"},";
  text2 += "{\"dataValue\":\"";
  text2 += "count";
  text2 += "\"}";
  text2 += "]}";
	Serial.println("Data end");
  server.send(200, "text/html", text2);
  count++;
}

void server_setup(){
  LittleFS.begin();
  server.on("/data", getData);
  server.on("/hour", handleHours);

	server.begin();
	Serial.println("HTTP server started");

  server.onNotFound([](){
      if(!handleFileRead(server.uri()))
          server.send(404, "text/plain", "FileNotFound");
  });
}

void server_loop() {
	server.handleClient();
}