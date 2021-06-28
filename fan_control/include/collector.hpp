#include <Arduino.h>

#include <vector>

using namespace std;

void collector_setup();

void collector_loop();

#define WEEK 1500
#define MONTH 750

class Collector
{
protected:
  float week_in[WEEK]; // 10 per hour, 1 week
  float week_out[1500]; // 10 per hour, 1 week
  float month_in[750]; // 1 per hour, about a month
  float month_out[750]; // 1 per hour, about a month
  float minute = 0 ;
  int counter = 0;

  String one_week( float[] );
  String one_month( float[] );

public:
  const int bucket = 30; // sampling every 2 sec

  void add(float in , float out) ;
  String week_data();
  String month_data();

};

extern Collector collector;
