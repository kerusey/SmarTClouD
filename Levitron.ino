/*  !!! important stuff:
magnet_objects 1 and 2 used for X axis (right) (left)
magnet_objects 3 and 4 used for Y axis (right) (left)
ultrasonic objects 1 and 2 used for X axis (right) (left)
ultrasonic objects 3 and 4 used for Y axis (right) (left)
!!!*/

 // you may also need a high variable "h"

#include "Ultrasonic.h"
#include <SPI.h> // i dont know shall we use it or not (is there any protocols (not funcs and methods!), that this lib supports)
 // globals ***************************************
// ports ***********************************************
#define Trig1 50                       // sensor A "Trig" pin
#define Echo1 51                       // sensor A "Echo" pin

#define Trig2 52                       // sensor B "Trig" pin
#define Echo2 53                       // sensor B "Echo" pin

#define Trig3 54                       // sensor C "Trig" pin
#define Echo3 55                       // sensor C "Echo" pin

#define Trig4 56                      // sensor D "Trig" pin
#define Echo4 57                      // sensor D "Echo" pin

#define SDI_1 7
#define CLK_1 8

#define SDI_2 35
#define CLK_2 36

#define SDI_3 58
#define CLK_3 59

#define SDI_4 70
#define CLK_4 71

#define CS 9                      // const ports for 4 resisto_coil objects

// ports **********************************************

#define HallS1 21
#define HallS2 22
#define HallS3 23
#define HallS4 24         // 4 hall sensor's ports


#define const_resistance 10.0         // variable default resistance of coils (better be over 10; best > const_delta_resistance * 10)
#define const_alpha 30                // variable (ultrasonic object's angle)
#define const_delta_resistance 3.906  // variable, equals step of resistor (in example used AD8400, with a step 1000/256 Ohm/step) 
#define max_coil_resistance 20        // could be variable, depending on your coil resistance (const max_coil_resistance = 2*coil_resistance), shows maximal approved resistance for resistor (paralleled coil) 

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

/*
class squad_container {  // used here to contain resistance before hall_check func change it (uleless in futuere)
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
*/

const float Baseline = 100;                 // distance between the transducers (aka c - sight) (cm)

class resisto_coil {
  
  int sdi;
  int clk;
  int cs;  // ports for resistor pci
  float resistance;

public:

 resisto_coil (int my_sdi, int my_clk) { // my_ input must be constant !!!
  resistance = const_resistance;
  sdi = my_sdi;
  clk = my_clk;
  cs = CS;
 }

  void boot () {
    pinMode(sdi, OUTPUT);
    pinMode(clk, OUTPUT);
    pinMode(cs, OUTPUT);
    digitalWrite(cs, HIGH);
  }

  int coil_resistance () {return resistance;}

  void change_coil_resistance (int res) {

      digitalWrite(cs, HIGH);             
      digitalWrite(sdi, HIGH);            
      digitalWrite(clk, LOW);             
      
      delayMicroseconds(1);               
      
      digitalWrite(cs, LOW);             
      
      delayMicroseconds(1);
      
      digitalWrite(sdi, LOW);
      
      delayMicroseconds(1);

      for (size_t i = 0 ; i < 2 ; ++i) {
        digitalWrite (clk, LOW);
        digitalWrite (clk, HIGH);
      }

      for (size_t i = 7 ; i >= 0 ; --i){
        digitalWrite (clk, LOW);
        
        int bt = bitRead(res, i);
        
        if (bt == 1) digitalWrite (sdi, HIGH);
        else digitalWrite (sdi, LOW);

        digitalWrite (clk, HIGH);
      }
      digitalWrite (cs, HIGH);
    }

};

// now creating a 4 megnetic coil objects, been controlled by variable resistor;
 
 resisto_coil magnet_object1 (SDI_1, CLK_1),
              magnet_object2 (SDI_2, CLK_2), // for X axis
              magnet_object3 (SDI_3, CLK_3),
              magnet_object4 (SDI_4, CLK_4); // for Y axis
 
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
            if (magnet_object1.coil_resistance() >= const_delta_resistance) magnet_object1.change_coil_resistance(-1); // buck
            if (magnet_object2.coil_resistance() < max_coil_resistance) magnet_object2.change_coil_resistance(1); // boost
          }

          while (Xdiviation < 0) {  // check deviation of left sight
            if (magnet_object1.coil_resistance() >= const_delta_resistance) magnet_object1.change_coil_resistance(1); // boost 
            if (magnet_object2.coil_resistance() < max_coil_resistance) magnet_object2.change_coil_resistance(-1); // buck
          }

          while (Xdiviation == 0) {
            Xdiviation = x.check_axis_orientary();
            delay(100); // variable
          }

            // end of checking X axis
      
      // check Y axis deviation
        
          while (Ydiviation > 0) {  // check deviation of right sight
            if (magnet_object3.coil_resistance() >= const_delta_resistance) magnet_object3.change_coil_resistance(-1); // buck
            if (magnet_object4.coil_resistance() < max_coil_resistance) magnet_object4.change_coil_resistance(1); // boost
          }

          while (Ydiviation < 0) {  // check deviation of left sight
            if (magnet_object3.coil_resistance() >= const_delta_resistance) magnet_object3.change_coil_resistance(1); // boost
            if (magnet_object4.coil_resistance() < max_coil_resistance) magnet_object4.change_coil_resistance(-1); // buck
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
    //      squad_container my_sq_container;
  //        my_sq_container.import_sq (magnet_object1.coil_resistance(), magnet_object2.coil_resistance(), magnet_object3.coil_resistance(), magnet_object4.coil_resistance()); // import all resistance of each coil before they'll be changed
 
          magnet_object1.change_coil_resistance (-int(magnet_object1.coil_resistance()));
          magnet_object2.change_coil_resistance (-int(magnet_object2.coil_resistance()));
          magnet_object3.change_coil_resistance (-int(magnet_object3.coil_resistance()));
          magnet_object4.change_coil_resistance (-int(magnet_object4.coil_resistance()));

        /** little summary. We have imported resistances to squad container*/
          do
            delay(3000);
          while (hall_check); // now we've waited for as much time as user needs to take levitating object away from coils
          // and we need to boot'em up again

//          my_sq_container.export_sq (magnet_object1.coil_resistance(), magnet_object2.coil_resistance(), magnet_object3.coil_resistance(), magnet_object4.coil_resistance());  // returns values of resistance of each coil back
          
          magnet_object1.change_coil_resistance (const_resistance);
          magnet_object2.change_coil_resistance (const_resistance);
          magnet_object3.change_coil_resistance (const_resistance);
          magnet_object4.change_coil_resistance (const_resistance);  //! ALL THOSE COMMENTS ARE BECAUSE I WANTED TO CONTAIN VALUES OF EACH COIL RESISTANCE
          
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
