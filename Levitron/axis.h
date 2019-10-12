#pragma once

#include "Ultrasonic.h"
#include "Status.h"

#define const_alpha 45
#define baseline 30  // (CM)
#define magnet_body_lenght 10  // (CM)
#define critical_height 7 // (CM)

namespace ax {

size_t height;
void read_height ();

class Axis {
  protected:
    size_t L1dist;
    size_t L2dist;
    Ultrasonic *ultra_object1;
    Ultrasonic *ultra_object2;
  public:

    void read_L1 ();
    void read_L2 ();

    axis (Ultrasonic &ultra_object1, Ultrasonic &ultra_object2);

    double check_axis_orientary ();

    ~axis ();

};
