#include <Arduino.h>

#include <vector>

using namespace std;

void collector_setup();

void collector_loop();

class Collector
{
protected:
  float week_in[1500]; // 10 per hour, 1 week
  float week_out[1500]; // 10 per hour, 1 week
  float month_in[750]; // 1 per hour, about a month
  float month_out[750]; // 1 per hour, about a month
  float minute = 0 ;
  int counter = 0;
  int bucket = 30; // sampling every 2 sec
public:

  void add(float in , float out) ;
  
};

extern Collector collector;
