#include "Ultrasonic.h"

 // globals ***************************************

#define Trig1 1                       // sensor A "Trig" pin
#define Echo1 2                       // sensor A "Echo" pin

#define Trig2 3                       // sensor B "Trig" pin
#define Echo2 4                       // sensor B "Echo" pin

#define Trig3 5                       // sensor C "Trig" pin
#define Echo3 6                       // sensor C "Echo" pin

#define Trig4 7                      // sensor D "Trig" pin
#define Echo4 8                      // sensor D "Echo" pin

#define Up1 9
#define Inc1 10
#define Cs1 11

#define Up2 12
#define Inc2 13
#define Cs2 14

#define Up3 15
#define Inc3 16
#define Cs3 17

#define Up4 18
#define Inc4 19
#define Cs4 20                      // inititializes 4 resisto_coil objects

#define const_resistance 3000

 // 4 ultrasonic objects
 
Ultrasonic ultrasonic1(Trig1, Echo1),
           ultrasonic2(Trig2, Echo2), // these are for x - axis

           ultrasonic3(Trig3, Echo3),
           ultrasonic4(Trig4, Echo4); // these - for y- axis

// resisto-coil class provide control coils via changing resistance of controllable resistor that been paralleled with the coil

class resisto_coil {
  
  int ud;
  int inc;
  int cs;
  int resistance;

public:

 resisto_coil (int my_ud, int my_inc, int my_cs) { // my_ input must be constant !!!
  resistance = const_resistance;
  ud = my_ud;
  inc = my_inc;
  cs = my_cs;
 }

 void boost_coil() {                   // 1step resistor boost
  
  digitalWrite(ud, HIGH);             //  U/D  goes up 1
  digitalWrite(inc, HIGH);            //  INC too
  digitalWrite(cs, LOW);              // turn on
  
  delayMicroseconds(1);               
  
  digitalWrite(inc, LOW);             
  
  delayMicroseconds(1);
  
  digitalWrite(inc, HIGH);
  
  delayMicroseconds(1);

  digitalWrite(cs, HIGH);             // turn off and runs EEPROM 
 }

 void buck_coil() {                         // 1step buck resistor
 
  digitalWrite(ud, LOW);        //  U/D  goes up 1
  digitalWrite(inc, HIGH);        //  INC too
  digitalWrite(cs, LOW);        // turn on
 
  delayMicroseconds(1);
 
  digitalWrite(inc, LOW);
 
  delayMicroseconds(1);
 
  digitalWrite(inc, HIGH);
 
  delayMicroseconds(1);

  digitalWrite(cs, HIGH);
 }

};

// now creating a 4 megnetic coil objects, been controlled by variable resistor;
 
 resisto_coil magnet_object1 (Up1, Inc1, Cs1),
              magnet_object2 (Up2, Inc2, Cs2), // for X axis
              magnet_object3 (Up3, Inc3, Cs3),
              magnet_object4 (Up4, Inc4, Cs4); // for Y axis

 class axis { // triangle sights a & b ; c - const

  int Adist;
  int Bdist;
  Ultrasonic *ultra_object1;
  Ultrasonic *ultra_object2;

public:

  void read_A (){
    Adist = ultra_object1->distanceRead();
  }

  void read_B (){
    Bdist = ultra_object2->distanceRead();
  }

  
  axis(Ultrasonic &ultra_object1, Ultrasonic &ultra_object2) {
    read_A();
    read_B();

    } // here is some kinda of initiative

  int check_axis_orientary () { // returns the axis inclination
    return (Adist - Bdist);
  }

 };

struct double_result {
  int result1;
  int result2;

  const double_result operator = (double_result my_result) {
    result1 = my_result.result1;
    result2 = my_result.result2;
  }
};

const float Baseline = 100;                 // distance between the transducers (aka c - sight) (cm)
 
 // globals ***************************************

void setup () {
  Serial.begin(9600);  
  
}

void loop () {

  axis x (ultrasonic1, ultrasonic2);
  axis y (ultrasonic3, ultrasonic4);
  
  
  double_result bias;
  bias = find_diviation (x, y);
}

double_result find_diviation (axis x, axis y){
   double_result sumup;
   sumup.result1 = x.check_axis_orientary();
   sumup.result2 = y.check_axis_orientary();
    return sumup;
}

