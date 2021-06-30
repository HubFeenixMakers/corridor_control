#include <Arduino.h>

#include <vector>

using namespace std;

void collector_setup();

void collector_loop();

// Set delay between sensor readings.
#define DELAY 3000 //3s , longer and the web requests time-out
#define MINUTE 120  // 6 min average
#define WEEK  1000  // 4 days worth of 6min sample
#define MONTH 750   // 1 month of hourly sample
#define PER_HOUR 10

class Collector
{
protected:
  float minute_in = 0 ;
  float minute_out = 0 ;


  int minute_counter = 0;
  int week_counter = 0;
  int month_counter = 0;

  void add_month(int from ) ;

  String one_week( float[] );
  String one_month( float[] );

public:
  float week_in[WEEK];
  float week_out[WEEK];

  float month_in[MONTH];
  float month_out[MONTH];

  void add_week(float in , float out) ;
  void add(float in , float out) ;

  String week_data();
  String month_data();

};

extern Collector collector;
