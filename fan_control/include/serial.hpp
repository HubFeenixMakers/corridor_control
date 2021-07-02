#include <Arduino.h>
#include <queue>

class WsSerial{
    std::queue<String> debug;

    public:
    inline void print(const String& line){   debug.push(line); }
    inline void println(const String& line){   debug.push(line); }
    inline void println(const float num){ println(String(num)) ; };

    inline const String& pop(){ const String& first = debug.front(); debug.pop(); return first;};
    inline bool empty(){ return debug.empty();};
};

static WsSerial debug_out;

#if(false)
#define DEBUG_OUT Serial
#define DEBUG_SERIAL true
#else
#define DEBUG_SERIAL false
#define DEBUG_OUT debug_out
#endif
