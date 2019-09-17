
#include "axis.h"

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif


void axis::read_A () {
  Adist = ultra_object1->read();
}

void axis::read_B () {
  Bdist = ultra_object2->read();
}

axis::axis(Ultrasonic &ultra_object1, Ultrasonic &ultra_object2) {
  read_A();
  read_B();

} // constructor

double axis::check_axis_orientary () { // returns the axis inclination (from the right sight)
  return (Adist * cos(const_alpha) - Bdist * cos(const_alpha));
}

axis::~axis () {}
