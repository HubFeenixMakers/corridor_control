#include "serial.hpp"
#include "server.hpp"

void WsSerial::print(const String& line){
  debug.push(line);
}
void WsSerial::println(const String& line){
  debug.push(line);
}

void serial_setup(){
  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it gat is: %u\n", client->lastId());
    }
    //send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!",NULL,millis(),1000);
  });
}

void serial_loop(){
#if DEBUG_SERIAL
  return;
#else
  if(debug_out.empty()) return ;
  const String & line = debug_out.pop();
  Serial.println(line.c_str());
  events.send(line.c_str() , "message");
#endif
}
