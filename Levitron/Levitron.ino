/*!!! important stuff:
  magnet_objects 1 and 2 used for X axis (right) (left)
  magnet_objects 3 and 4 used for Y axis (right) (left)
  ultrasonic objects 1 and 2 used for X axis (right) (left)
  ultrasonic objects 3 and 4 used for Y axis (right) (left)
  !!!*/

// you may also need a high variable "height"

#include "Ultrasonic.h"
// #include "squad_container.cpp"
#include "resisto_coil.h"
#include "axis.h"
// #include <SPI.h> // i dont know shall we use it or not (is there any protocols (not funcs and methods!), that this lib supports)

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

#define TrigH 72 
#define EchoH 73

#define SDI_1 7
#define CLK_1 8

#define SDI_2 35
#define CLK_2 36

#define SDI_3 58
#define CLK_3 59

#define SDI_4 70
#define CLK_4 71

#define CS 9                      // const ports for 4 resisto_coil objects
/*
  #define HallS_A1 A15
  #define HallS_A2 A14
  #define HallS_A3 A13
  #define HallS_A4 A12        // they're not used in this program, but if you need you can uncomment them
*/
#define HallS_D1 72
#define HallS_D2 73
#define HallS_D3 74
#define HallS_D4 75         // 4 hall sensor's ports

#define Relay_D 76      // Relay digital port

// ports **********************************************

// #define const_resistance 10.0          // variable default resistance of coils (better be over 10; best > const_delta_resistance * 10) <- see resisto_coil.h
// #define const_alpha 30                 // variable (ultrasonic object's angle) <- already written in files axis.h / axis.cpp 
#define const_delta_resistance 3.906   // variable, equals step of resistor (in example used AD8400, with a step 1000/256 Ohm/step) 
#define max_coil_resistance 20         // could be variable, depending on your coil resistance (const max_coil_resistance = 2*coil_resistance), shows maximal approved resistance for resistor (paralleled coil) 
#define Baseline 100                   // distance between the transducers (aka c - sight) (cm)

// 4 ultrasonic objects

Ultrasonic ultrasonic_object1 (Trig1, Echo1),
           ultrasonic_object2 (Trig2, Echo2), // these are for x - axis

           ultrasonic_object3 (Trig3, Echo3),
           ultrasonic_object4 (Trig4, Echo4), // these - for y - axis

           ultrasonic_object_height (TrigH, EchoH); // special object, that contains height between station and levitating object
           
// resisto-coil class provide control coils via changing resistance of controllable resistor that been paralleled with the coil

// now creating a 4 megnetic coil objects, been controlled by variable resistor;

resisto_coil magnet_object1 (SDI_1, CLK_1),
             magnet_object2 (SDI_2, CLK_2), // for X axis
             magnet_object3 (SDI_3, CLK_3),
             magnet_object4 (SDI_4, CLK_4); // for Y axis

// globals ***************************************


void setup () {  // __init__ & set
  Serial.begin(9600);

  // now we need to boot up the magnet objects:

  magnet_object1.boot();
  magnet_object2.boot();
  magnet_object3.boot();
  magnet_object4.boot();

  // booting magnet object obj

  // setting Hall sensor

  pinMode(HallS_D1, INPUT);
  pinMode(HallS_D2, INPUT);
  pinMode(HallS_D3, INPUT);
  pinMode(HallS_D4, INPUT);

  // setting Hall sensors

  // setting Relay obj

  digitalWrite (Relay_D, LOW);

  // setting Relay obj

}


bool hall_check () { // checks "Hall exeption" 
  if (digitalRead(HallS_D1) == LOW || digitalRead(HallS_D2) == LOW || digitalRead(HallS_D3) == LOW || digitalRead(HallS_D4) == LOW)
    return true;
  else return false;
}

size_t my_height () { return ultrasonic_object_height.distanceRead(); } // havent released yet (probably no need)

void solve_axis_deviation (axis &x, resisto_coil magnet_object1, resisto_coil magnet_object2) {
  double deviation = x.check_axis_orientary();
    if (deviation > 0) {  // check deviation of right sight
      if (magnet_object1.coil_resistance() >= const_delta_resistance) magnet_object1.change_coil_resistance(1); // boost
      if (magnet_object2.coil_resistance() < max_coil_resistance) magnet_object2.change_coil_resistance(-1); // buck
    }

    if (deviation < 0) {  // check deviation of left sight
      if (magnet_object1.coil_resistance() >= const_delta_resistance) magnet_object1.change_coil_resistance(-1); // buck
      if (magnet_object2.coil_resistance() < max_coil_resistance) magnet_object2.change_coil_resistance(1); // boost
    }
}

void correction (axis &x, axis &y) { // this is the main function of control coils
  while (true) {
    // check X axis deviation
    if (!hall_check) { 
      solve_axis_deviation (x, magnet_object1, magnet_object2);
      solve_axis_deviation (y, magnet_object3, magnet_object4);
    }
    
    /* now we need to read hall sensor's input */
    else  // if hall_check == true
    digitalWrite (Relay_D, HIGH); // coil relay exeption 
      //      squad_container my_sq_container;
      //        my_sq_container.import_sq (magnet_object1.coil_resistance(), magnet_object2.coil_resistance(), magnet_object3.coil_resistance(), magnet_object4.coil_resistance()); // import all resistance of each coil before they'll be changed
/*
      magnet_object1.change_coil_resistance (-int(magnet_object1.coil_resistance () / const_delta_resistance));
      magnet_object2.change_coil_resistance (-int(magnet_object2.coil_resistance () / const_delta_resistance));
      magnet_object3.change_coil_resistance (-int(magnet_object3.coil_resistance () / const_delta_resistance));
      magnet_object4.change_coil_resistance (-int(magnet_object4.coil_resistance () / const_delta_resistance));
*/ 
      /** little summary. We have imported resistances to squad container*/
      do
        delay(3000);
      while (hall_check); // now we've waited for as much time as user needs to take levitating object away from coils
      // and we need to boot'em up again
    digitalWrite (Relay_D, LOW);
      //          my_sq_container.export_sq (magnet_object1.coil_resistance(), magnet_object2.coil_resistance(), magnet_object3.coil_resistance(), magnet_object4.coil_resistance());  // returns values of resistance of each coil back
/*
      magnet_object1.change_coil_resistance (const_resistance);
      magnet_object2.change_coil_resistance (const_resistance);
      magnet_object3.change_coil_resistance (const_resistance);
      magnet_object4.change_coil_resistance (const_resistance);  //! ALL THOSE COMMENTS ARE BECAUSE I WANTED TO CONTAIN VALUES OF EACH COIL RESISTANCE
*/
      // here we go back


  } // while (true)
} // func

void loop () { 
  axis x (ultrasonic_object1, ultrasonic_object2),
       y (ultrasonic_object3, ultrasonic_object4);

  correction (x, y);
} 
