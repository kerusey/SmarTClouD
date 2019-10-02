#pragma once

#include "Ultrasonic.h"

#define const_alpha 45
#define baseline 30  // (CM)
#define magnet_body_lenght 10  // (CM)

class axis { // triangle sights a & b ; c - const
  protected:

    int Adist;
    int Bdist;
    Ultrasonic *ultra_object1;
    Ultrasonic *ultra_object2;

  public:

    void read_A ();

    void read_B ();

    axis (Ultrasonic &ultra_object1, Ultrasonic &ultra_object2);

    double check_axis_orientary ();
    
    ~axis ();
    
};
