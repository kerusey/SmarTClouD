/*!!! important stuff:
  magnet_objects 1 and 2 used for X axis (right) (left)
  magnet_objects 3 and 4 used for Y axis (right) (left)
  ultrasonic objects 1 and 2 used for X axis (right) (left)
  ultrasonic objects 3 and 4 used for Y axis (right) (left)
  !!!*/

#include "Ports.h"
#include "Ultrasonic.h"
#include "Axis.h"
#include "Pwm_coil.h"
#include "Status.h"

// setting Status object
st::Status core;          // allows to check any deviations of incline/height or check hall sensor exeption
// setting Status object

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

void solve_axis_deviation (ax::Axis &x, Pwm_coil &_magnet_object1, Pwm_coil &_magnet_object2) { // checks deviation of the one axis
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

void correction (ax::Axis &x, ax::Axis &y) { // this is the main function of control coils
  while (true) {
    // check X axis deviation
    if (!core.NT_critical()) {
      solve_axis_deviation (x, magnet_object1, magnet_object2); // solve X axis deviation
      solve_axis_deviation (y, magnet_object3, magnet_object4); // solve Y axis deviation
    }

    /* now we need to stop the all process until Status will not be critical */
    else  // if hall_check == true
    digitalWrite (Relay_D, HIGH); // coil relay exeption
      do {
        delay(3000);
        core.st::Status::resolve_status();
        }
      while (core.NT_critical()); // now we've waited for as much time as user needs to take levitating object away from coils
      // and we need to set relay down again
    digitalWrite (Relay_D, LOW);

  } // while (true)
} // func

void loop () {
  ax::Axis x (ultrasonic_object1, ultrasonic_object2),
           y (ultrasonic_object3, ultrasonic_object4);

  correction (x, y);
}
