#include <Arduino.h>
#include <queue>

class WsSerial{
    std::queue<String> debug;

    public:
    inline void print(const String& line){  
        // enable debug the debugging Serial.println(line.c_str()); 
        debug.push(line); 
        }
    inline void println(const String& line){
        // enable debug the debugging Serial.println(line.c_str()); 
        debug.push(line); 
        }
    inline void println(const float num){ println(String(num)) ; };

    inline const String& first(){ return debug.front();};
    inline void pop(){  debug.pop(); };
    inline bool empty(){ return debug.empty();};
};

extern WsSerial debug_out;

#if(false)
#define DEBUG_OUT Serial
#define DEBUG_SERIAL true
#else
#define DEBUG_SERIAL false
#define DEBUG_OUT debug_out
#endif
