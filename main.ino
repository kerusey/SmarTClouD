#include "Ultrasonic.h"

 // globals ***************************************

#define Trig1 4                       //sensor A "Trig" pin
#define Echo1 5                       //sensor A "Echo" pin

#define Trig2 6                       //sensor B "Trig" pin
#define Echo2 7                       //sensor B "Echo" pin

#define Trig3 8                       //sensor C "Trig" pin
#define Echo3 9                       //sensor C "Echo" pin

#define Trig4 10                       //sensor D "Trig" pin
#define Echo4 11                       //sensor D "Echo" pin

 // 4 ultrasonic objects
 
Ultrasonic ultrasonic1(Trig1, Echo1);
Ultrasonic ultrasonic2(Trig2, Echo2); // these are for x - axis

Ultrasonic ultrasonic3(Trig3, Echo3);
Ultrasonic ultrasonic4(Trig4, Echo4); // these - for y- axis

 class axis { // triangle sights a & b ; c - const

  int Adist;
  int Bdist;
  Ultrasonic *ultra_object1;
  Ultrasonic *ultra_object2;

public:

  void read_A (){
    Adist = ultra_object1.distanceRead();
  }

  void read_B (){
    Bdist = ultra_object2.distanceRead();
  }

  
  axis(Ultrasonic *ultra_object1, Ultrasonic *ultra_object2) {
    read_A();
    read_B();

    } // here is some kinda of initiative

  int check_axis_orientary () { // returns the axis inclination
    return (Adist - Bdist);
  }

 };


const float Baseline = 100;                 // distance between the transducers (aka c - sight) (cm)
 
 // globals ***************************************

void setup {
  Serial.begin(9600);

  axis x (ultrasonic1, ultrasonic2);
  axis y (ultrasonic3, ultrasonic4);
  
  
}

void loop {
  
}



