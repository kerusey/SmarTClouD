#include "Ultrasonic.h"
/*  !!! important stuff:
magnet_objects 1 and 2 used for X axis (right) (left)
magnet_objects 3 and 4 used for Y axis (right) (left)
ultrasonic objects 1 and 2 used for X axis (right) (left)
ultrasonic objects 3 and 4 used for Y axis (right) (left)
!!!*/

 // you may also need a high variable "h"



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

#define HallS1 21
#define HallS2 22
#define HallS3 23
#define HallS4 24         // 4 hall sensor's ports


#define const_resistance 10.0           // variable default resistance of coils (better be over 10; best > const_delta_resistance * 10)
#define const_alpha 30                  // variable (ultrasonic object's angle)
#define const_delta_resistance 3.906  // variable, equals step of resistor (in example used AD8400, with a step 1000/256 Ohm/step) 


 // 4 ultrasonic objects
 
Ultrasonic ultrasonic_object1 (Trig1, Echo1),
           ultrasonic_object2 (Trig2, Echo2), // these are for x - axis

           ultrasonic_object3 (Trig3, Echo3),
           ultrasonic_object4 (Trig4, Echo4); // these - for y - axis

// resisto-coil class provide control coils via changing resistance of controllable resistor that been paralleled with the coil

 class axis { // triangle sights a & b ; c - const
protected:

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

    } // constructor

  int check_axis_orientary () { // returns the axis inclination (from the right sight)
    return (Adist*cos(const_alpha) - Bdist*cos(const_alpha)); 
  }

 };

class squad_container {  // used here to contain resistance before hall_check func change it
  float squad_member1;
  float squad_member2;
  float squad_member3;
  float squad_member4;

public:
 
    void import_sq (float sm1, float sm2, float sm3, float sm4){
      squad_member1 = sm1;
      squad_member2 = sm2;
      squad_member3 = sm3;
      squad_member4 = sm4;
    }

    void export_sq (float *sm1, float *sm2, float *sm3, float *sm4){
      *sm1 = squad_member1;
      *sm2 = squad_member2;
      *sm3 = squad_member3;
      *sm4 = squad_member4;
    }
};


const float Baseline = 100;                 // distance between the transducers (aka c - sight) (cm)

class resisto_coil {
  
  int ud;
  int inc;
  int cs;
  float resistance;

public:

 resisto_coil (int my_ud, int my_inc, int my_cs) { // my_ input must be constant !!!
  resistance = const_resistance;
  ud = my_ud;
  inc = my_inc;
  cs = my_cs;
 }

  void boot () {
    pinMode(inc, OUTPUT);
    pinMode(ud, OUTPUT);
    pinMode(cs, OUTPUT);
    digitalWrite(cs, HIGH);
  }

  int coil_resistance () {return resistance;}

  void boost_coil (size_t delta = 1) {                   // 1step resistor boost
    for (size_t i = 0 ; i < delta ; ++i) {
      digitalWrite(ud, HIGH);             //  U/D  goes up 1
      digitalWrite(inc, HIGH);            //  INC too
      digitalWrite(cs, LOW);              // turn on
      
      delayMicroseconds(1);               
      
      digitalWrite(inc, LOW);             
      
      delayMicroseconds(1);
      
      digitalWrite(inc, HIGH);
      
      delayMicroseconds(1);

      digitalWrite(cs, HIGH);             // turn off and runs EEPROM
      resistance += const_delta_resistance;                   
    }
 }

  void buck_coil (size_t delta = 1) {                         // 1step buck resistor
    for (size_t i = 0 ; i < delta ; ++i){
      digitalWrite(ud, LOW);        //  U/D  goes down 1
      digitalWrite(inc, HIGH);      //  INC too
      digitalWrite(cs, LOW);        // turn on
     
      delayMicroseconds(1);
     
      digitalWrite(inc, LOW);
     
      delayMicroseconds(1);
     
      digitalWrite(inc, HIGH);
     
      delayMicroseconds(1);

      digitalWrite(cs, HIGH);
      resistance -= const_delta_resistance;
    }
  }

};

// now creating a 4 megnetic coil objects, been controlled by variable resistor;
 
 resisto_coil magnet_object1 (Up1, Inc1, Cs1),
              magnet_object2 (Up2, Inc2, Cs2), // for X axis
              magnet_object3 (Up3, Inc3, Cs3),
              magnet_object4 (Up4, Inc4, Cs4); // for Y axis
 
 // globals ***************************************

bool hall_check (){  
  if (digitalRead(HallS1) == LOW || digitalRead(HallS2) == LOW || digitalRead(HallS3) == LOW || digitalRead(HallS4) == LOW) 
    return true;
  else return false;
} 


void correction (axis &x, axis &y) { // this is the main function of control coils
  
  int Xdiviation = x.check_axis_orientary();
  int Ydiviation = y.check_axis_orientary();
    
    while (true) {
      
      // check X axis deviation
        if (!hall_check) {
          while (Xdiviation > 0) {  // check deviation of right sight
            magnet_object1.buck_coil();
            magnet_object2.boost_coil();
          }

          while (Xdiviation < 0) {  // check deviation of left sight
            magnet_object1.boost_coil();
            magnet_object2.buck_coil();
            }

          while (Xdiviation == 0) {
            Xdiviation = x.check_axis_orientary();
            delay(100); // variable
          }

            // end of checking X axis
      
      // check Y axis deviation
        
          while (Ydiviation > 0) {  // check deviation of right sight
            magnet_object3.buck_coil();
            magnet_object4.boost_coil();
          }

          while (Ydiviation < 0) {  // check deviation of left sight
            magnet_object3.boost_coil();
            magnet_object4.buck_coil(); 
            }

          while (Ydiviation == 0) { 
            Ydiviation = y.check_axis_orientary();
            delay(100); // variable
          }

            // end of checking Y axis 

          Xdiviation = x.check_axis_orientary();
          Ydiviation = y.check_axis_orientary();

          delay(100); // variable
        }
/* now we need to read hall sensor's input */
      else { // if hall_check == true 
          squad_container my_sq_container;
          my_sq_container.import_sq (magnet_object1.coil_resistance(), magnet_object2.coil_resistance(), magnet_object3.coil_resistance(), magnet_object4.coil_resistance()); // import all resistance of each coil before they'll be changed
 
          magnet_object1.buck_coil(int(magnet_object1.coil_resistance()));
          magnet_object2.buck_coil(int(magnet_object2.coil_resistance()));
          magnet_object3.buck_coil(int(magnet_object3.coil_resistance()));
          magnet_object4.buck_coil(int(magnet_object4.coil_resistance()));

        /** little summary. We have imported resistances to squad container*/
          do
            delay(3000);
          while (hall_check); // now we've waited for as much time as user needs to take levitating object away from coils
          // and we need to boot'em up again

          my_sq_container.export_sq (magnet_object1.coil_resistance(), magnet_object2.coil_resistance(), magnet_object3.coil_resistance(), magnet_object4.coil_resistance());  // returns values of resistance of each coil back
          
          magnet_object1.boost_coil (int(magnet_object1.coil_resistance()));
          magnet_object2.boost_coil (int(magnet_object2.coil_resistance()));
          magnet_object3.boost_coil (int(magnet_object3.coil_resistance()));
          magnet_object4.boost_coil (int(magnet_object4.coil_resistance()));
          
          // here we go back

        } // hall_check == true "exeption"
      
    } // while (true)
 } // func 




void setup () {
  Serial.begin(9600);  
  
  // now we need to boot up the magnet objects:

  magnet_object1.boot();
  magnet_object2.boot();
  magnet_object3.boot();
  magnet_object4.boot();

    pinMode(HallS1, INPUT);
    pinMode(HallS2, INPUT);
    pinMode(HallS3, INPUT);
    pinMode(HallS4, INPUT);

}

void loop () {
  axis x (ultrasonic_object1, ultrasonic_object2),
     y (ultrasonic_object3, ultrasonic_object4);

     correction (x, y);
}
