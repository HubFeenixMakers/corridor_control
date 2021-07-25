#include "collector.hpp"
#include "serial.hpp"

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

WsSerial debug_out;

// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor


// mini https://chewett.co.uk/blog/1066/pin-numbering-for-wemos-d1-mini-esp8266/
DHT dht_in(1, DHT11);  // D2 on mini , tx, 01 on basic
DHT dht_out(3, DHT11); // D1 on mini , rx 03 on basic

Collector collector;

void collector_setup(){
  // Initialize device.
  dht_in.begin();
  dht_out.begin();
  pinMode(RELAY_BUILTIN , OUTPUT);
  digitalWrite( RELAY_BUILTIN , LOW);
  collector.start();
}

void Collector::start(){
  week_counter = 0;
  month_counter = 0;
}

void collector_loop(){
  delay(DELAY);
  // Get temperature event and print its value.
  float in = dht_in.readTemperature();
  float out = dht_out.readTemperature();
  collector.add(in , out);
}

void Collector::add(float in , float out)
{
  DEBUG_OUT.println(String("Temp. in/out (" ) + String(MINUTE - minute_counter) + "):" + String(in)  +  " / " + String(out));
  if(isnan(in) ) return ;
  if(isnan(out) ) return ;
  minute_in += in;
  minute_out += out;
  minute_counter++ ;
  if(minute_counter >= MINUTE) {
    add_week(minute_in/MINUTE , minute_out / MINUTE);
    minute_in = 0;
    minute_out = 0;
    minute_counter = 0;
  }
}

void Collector::add_week(float in , float out){
  switch_logic(in , out);
  week_in[week_counter] = in;
  week_out[week_counter] = out;
  if((week_counter % PER_HOUR) == 0){
    add_month( week_counter - PER_HOUR);
  }
  if(week_counter > max_week) max_week = week_counter ;
  week_counter++ ;
  if(week_counter >= WEEK) {
    week_counter = 0;
  }
}

void Collector::switch_logic(float in , float out){
  if(out > (in + 1.0) ){
    digitalWrite( RELAY_BUILTIN , HIGH);
    DEBUG_OUT.println("Switching on" );  
  }else if( in > (out - 0.5 ) ) {
    digitalWrite( RELAY_BUILTIN , LOW);
    DEBUG_OUT.println( "Switching off" );
  } else {
    DEBUG_OUT.println( "No Switching" );
  }
}

void Collector::add_month(int from){
  if( from < 0) return;
  if( from + PER_HOUR > WEEK) return ;
  float month_i = 0;
  float  month_o = 0;
  for(int i = 0 ; i < PER_HOUR ; i++){
    month_i += week_in[ from + i];
    month_o += week_out[ from + i];
  }
  month_in[month_counter] = month_i / PER_HOUR;
  month_out[month_counter] = month_o / PER_HOUR ;
  if( month_counter > max_month) max_month = month_counter ;
  month_counter++ ;
  if(month_counter >= MONTH) {
    month_counter = 0;
  }
}


String Collector::week_data(int at){
  if( at < WEEK){
    if( at > max_week ) at = max_week;
    return String(week_in[at] , 2) ;
  }else{
  if( at > (max_week + WEEK) ) at = max_week + WEEK;
  return String(week_out[at - WEEK] , 2) ;
  }
}


String Collector::month_data(int at){
  if( at < MONTH){
    if(at > max_month) at = max_month ;
    return String(month_in[at] , 2) ;
  }else{
    if(at > (max_month + MONTH)) at = max_month + MONTH ;
    return String(month_out[at - MONTH] , 2) ;
  }
}