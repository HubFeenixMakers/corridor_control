#include <Arduino.h>
#include <queue>

void serial_setup();
void serial_loop();

class WsSerial{
    std::queue<String> debug;

    public:
    void print(const String& );
    void println(const String& );
    inline void println(const float num){ println(String(num)) ; };

    inline const String& pop(){ const String& first = debug.front(); debug.pop(); return first;};
    inline bool empty(){ return debug.empty();};
};


#if(false)
#define DEBUG_OUT Serial
#define DEBUG_SERIAL true
#else
#define DEBUG_SERIAL false
static WsSerial debug_out;
#define DEBUG_OUT debug_out
#endif
