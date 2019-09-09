/*!!! important stuff:
  magnet_objects 1 and 2 used for X axis (right) (left)
  magnet_objects 3 and 4 used for Y axis (right) (left)
  ultrasonic objects 1 and 2 used for X axis (right) (left)
  ultrasonic objects 3 and 4 used for Y axis (right) (left)
  !!!*/

// you may also need a high variable "height"

#include "Ports.h"
#include "Ultrasonic.h"
// #include "squad_container.h"
// #include "resisto_coil.h"
#include "axis.h"
#include "Protector.h"
#include “PWM_controller.h”
// #include <SPI.h> // i dont know shall we use it or not (is there any protocols (not funcs and methods!), that this lib supports)

// globals ***************************************
// #define const_resistance 10.0          // variable default resistance of coils (better be over 10; best > const_delta_resistance * 10) <- see resisto_coil.h
// #define const_alpha 30                 // variable (ultrasonic object's angle) <- already written in files axis.h / axis.cpp
// #define const_delta_resistance 3.906   // variable, equals step of resistor (in example used AD8400, with a step 1000/256 Ohm/step) <- see resisto_coil.h file
// #define max_coil_resistance 20         // could be variable, depending on your coil resistance (const max_coil_resistance = 2*coil_resistance), shows maximal approved resistance for resistor (paralleled coil)
// #define Baseline 100                   // distance between the transducers (aka c - sight) (cm) (Actually not need)

// 4 ultrasonic objects

Ultrasonic ultrasonic_object1 (Trig1, Echo1),
           ultrasonic_object2 (Trig2, Echo2), // these are for x - axis

           ultrasonic_object3 (Trig3, Echo3),
           ultrasonic_object4 (Trig4, Echo4); // these - for y - axis

//         ultrasonic_object_height (TrigH, EchoH); // special object, that contains height between station and levitating object (not used in this project) 

// resisto-coil class provide control coils via changing resistance of controllable resistor that been paralleled with the coil

resisto_coil magnet_object1 (UD_1, INC_1),
             magnet_object2 (UD_2, INC_2), // for X axis
                           
             magnet_object3 (UD_3, INC_3),
             magnet_object4 (UD_4, INC_4); // for Y axis

// now creating a 4 megnetic coil objects, been controlled by variable resistor;
    
// globals ***************************************


void setup () {  // __init__ & set
  Serial.begin(9600);

  // now we need to boot up the magnet objects:

  magnet_object1.resisto_coil::boot();
  magnet_object2.resisto_coil::boot();
  magnet_object3.resisto_coil::boot();
  magnet_object4.resisto_coil::boot();

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
  return false;
}

// size_t my_height () { return ultrasonic_object_height.read(); } // havent released yet (probably no need)

void solve_axis_deviation (axis &x, resisto_coil &_magnet_object1, resisto_coil &_magnet_object2) {
  double deviation = x.check_axis_orientary();
    if (deviation > 0) {  // check deviation of right sight
      if (_magnet_object1.get_pot_resistance() >= const_delta_resistance) _magnet_object1.resisto_coil::boost(); // boost
      if (_magnet_object2.get_pot_resistance() < potentiometer_resistance) _magnet_object2.resisto_coil::buck(); // buck
    }

    if (deviation < 0) {  // check deviation of left sight
      if (_magnet_object1.get_pot_resistance() >= const_delta_resistance) _magnet_object1.resisto_coil::buck(); // buck
      if (_magnet_object2.get_pot_resistance() < potentiometer_resistance) _magnet_object2.resisto_coil::boost();// boost
    }
}

void correction (axis &x, axis &y) { // this is the main function of control coils
  while (true) {
    // check X axis deviation
    if (!hall_check () ||  global_protect (magnet_object1, magnet_object2, magnet_object3,  magnet_object4)) {
      solve_axis_deviation (x, magnet_object1, magnet_object2);
      solve_axis_deviation (y, magnet_object3, magnet_object4);
    }

    /* now we need to read hall sensor's input /
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
      /** little summary. We have imported resistances to squad container */
      do
        delay(3000);
      while (hall_check() || global_protect (magnet_object1, magnet_object2, magnet_object3,  magnet_object4)); // now we've waited for as much time as user needs to take levitating object away from coils
      // and we need to boot'em up again
    digitalWrite (Relay_D, LOW);
      //          my_sq_container.export_sq (magnet_object1.coil_resistance(), magnet_object2.coil_resistance(), magnet_object3.coil_resistance(), magnet_object4.coil_resistance());  // returns values of resistance of each coil back
/*
      magnet_object1.change_coil_resistance (const_resistance);
      magnet_object2.change_coil_resistance (const_resistance);
      magnet_object3.change_coil_resistance (const_resistance);
      magnet_object4.change_coil_resistance (const_resistance);  //! ALL THOSE COMMENTS ARE BECAUSE I WANTED TO CONTAIN VALUES OF EACH POTENTIOMETER RESISTANCE (NOT NESSESARY AT ALL)
*/

  } // while (true)
} // func

void loop () {
  axis x (ultrasonic_object1, ultrasonic_object2),
       y (ultrasonic_object3, ultrasonic_object4);

  correction (x, y);
}
