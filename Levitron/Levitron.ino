/*!!! important stuff:
  magnet_objects 1 and 2 used for X axis (right) (left)
  magnet_objects 3 and 4 used for Y axis (right) (left)
  ultrasonic objects 1 and 2 used for X axis (right) (left)
  ultrasonic objects 3 and 4 used for Y axis (right) (left)
  !!!*/

#include "Ports.h"
#include "Ultrasonic.h"
#include "axis.h"
#include "PWM_controller.h"
#include "Status.h"

// globals ***************************************

// setting Status object
Status core;
// setting Status object

// setting 4 ultrasonic objects

Ultrasonic ultrasonic_object1 (Trig1, Echo1),
           ultrasonic_object2 (Trig2, Echo2), // these are for x - axis

           ultrasonic_object3 (Trig3, Echo3),
           ultrasonic_object4 (Trig4, Echo4); // these - for y - axis

// setting 4 ultrasonic objects

// pwm_coil class provide control coils via changing voltage on PWM controllers that been connected to the coil

// now creating a 4 megnetic coil objects, been controlled by PWM controllers; **

pwm::coil magnet_object1 (PWM_pin1, SERIAL1),
          magnet_object2 (PWM_pin2, SERIAL2), // for X axis

          magnet_object3 (PWM_pin3, SERIAL3),
          magnet_object4 (PWM_pin4, SERIAL4); // for Y axis

// now creating a 4 megnetic coil objects, been controlled by PWM controllers; **

// globals ***************************************


void setup () {  // __init__ & set
  Serial.begin(9600);

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

void solve_axis_deviation (axis &x, pwm::coil &_magnet_object1, pwm::coil &_magnet_object2) { // checks deviation of the one axis
  size_t deviation = x.check_axis_orientary();
    if (deviation > 0) {  // check deviation of right sight
      if (_magnet_object1.get_percent() < 100) _magnet_object1.boost(); // boost
      if (_magnet_object2.get_percent() >= 1) _magnet_object2.buck(); // buck
    }

    if (deviation < 0) {  // check deviation of left sight
      if (_magnet_object1.get_percent() >= 1) _magnet_object1.buck(); // buck
      if (_magnet_object2.get_percent() < 100) _magnet_object2.boost(); // boost
    }
}

void correction (axis &x, axis &y) { // this is the main function of control coils
  while (true) {
    // check X axis deviation
    if (!hall_check () ||  !global_protect (magnet_object1, magnet_object2, magnet_object3,  magnet_object4) || core.critical()) {
      solve_axis_deviation (x, magnet_object1, magnet_object2); // solve X axis deviation
      solve_axis_deviation (y, magnet_object3, magnet_object4); // solve Y axis deviation
    }

    /* now we need to read hall sensor's input */
    else  // if hall_check == true
    digitalWrite (Relay_D, HIGH); // coil relay exeption
      do
        delay(3000);
      while (hall_check() || global_protect (magnet_object1, magnet_object2, magnet_object3,  magnet_object4)); // now we've waited for as much time as user needs to take levitating object away from coils
      // and we need to set relay down again
    digitalWrite (Relay_D, LOW);

  } // while (true)
} // func

void loop () {
  axis x (ultrasonic_object1, ultrasonic_object2),
       y (ultrasonic_object3, ultrasonic_object4);

  correction (x, y);
}
