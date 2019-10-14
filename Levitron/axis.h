#pragma once

#include "Ultrasonic.h"
#include "Status.h"
#include "Ports.h"

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#define const_alpha 45
#define baseline 30  // (CM)
#define magnet_body_lenght 10  // (CM)

// 4 ultrasonic objects
Ultrasonic ultrasonic_object1 (Trig1, Echo1),
           ultrasonic_object2 (Trig2, Echo2), // these are for x - axis
    
           ultrasonic_object3 (Trig3, Echo3),
           ultrasonic_object4 (Trig4, Echo4); // these - for y - axis
// 4 ultrasonic objects

namespace ax {
size_t height;
void read_height ();
Ultrasonic *ultra_height(TrigH, EchoH);

class Axis {
  protected:
    size_t L1_dist;
    size_t L2_dist;
    Ultrasonic *ultra_object1;
    Ultrasonic *ultra_object2;
  public:
    void read_L1 ();
    void read_L2 ();
    bool check_right_half ();
    bool check_left_half ();
    Axis (Ultrasonic &ultra_object1, Ultrasonic &ultra_object2);
    int check_axis_orientary ();
    ~Axis ();
};
};
