#include "collector.hpp"

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

// Set delay between sensor readings based on sensor details.
uint32_t delayMS = 3000 ;


// mini https://chewett.co.uk/blog/1066/pin-numbering-for-wemos-d1-mini-esp8266/
DHT dht_in(4, DHT11);  // D2 on mini
DHT dht_out(5, DHT11); // D1 on mini

Collector collector;

void collector_setup(){
  // Initialize device.
  dht_in.begin();
  dht_out.begin();
  for( int a = 0; a < 4* WEEK*collector.bucket ; a = a + 1 ) {
    collector.add( random(10, 30) , random(10 , 30)  );
  }
}

void collector_loop(){
  delay(delayMS);

  // Get temperature event and print its value.
  Serial.print(F("Temperature inside: "));
  Serial.print(dht_in.readTemperature());
  Serial.println(F("°C"));
  Serial.print(F("Temperature outside: "));
  Serial.print(dht_out.readTemperature());
  Serial.println("°C");
}

void Collector::add(float in , float out)
{
  minute += in;
  counter++ ;
  if(counter % bucket){
    int at_week = counter / bucket; 
    week_in[at_week] = minute / bucket;
    minute = 0;
  }
  if(counter % (bucket*bucket)){
    int at_week = counter / bucket; 
    month_in[at_week] = minute / bucket;
  counter = 0;
  }
}

String Collector::one_week(float week[]){
  String data = "[";
  data += week[0];
  for( int a = 1; a < WEEK ; a = a + 1 ) {
    data += "," ; 
    data += week[a] ;
  }
  return data + "]";
}

String Collector::week_data(){
  String data = "[";
  return data + one_week(week_in) + "," + one_week(week_out) + "]";
}

String Collector::one_month(float month[]){
  String data = "[";
  data += month[0];
  for( int a = 1; a < MONTH ; a = a + 1 ) {
    data += "," ; 
    data += month[a] ;
  }
  return data + "]";
}

String Collector::month_data(){
  String data = "[";
  return data + one_month(month_in) + "," + one_month(month_out) + "]";
}
