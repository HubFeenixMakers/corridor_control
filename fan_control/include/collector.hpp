#include <vector>
using namespace std;

class Collector
{
protected:
  float week[100];
  float month[100];
  float minute = 0 ;
  int counter = 0;
  int max = 100 ;
  int bucket = 10;
public:

  void add(float val) 
  {
    minute += val;
    counter++ ;
    if(counter % bucket){
      int at_week = counter / bucket; 
      week[at_week] = minute / bucket;
      minute = 0;
    }
    if(counter % (bucket*bucket)){
      int at_week = counter / bucket; 
      month[at_week] = minute / bucket;
    counter = 0;
    }

  }
};