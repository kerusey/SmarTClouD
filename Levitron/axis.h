#pragma once

#include "Ultrasonic.h"
#include "Status.h"

#define const_alpha 45
#define baseline 30  // (CM)
#define magnet_body_lenght 10  // (CM)

class axis { // triangle sights a & b ; c - const
  protected:

    int Adist;
    int Bdist;
    int height;
    Ultrasonic *ultra_object1;
    Ultrasonic *ultra_object2;

  public:

    void read_A ();

    void read_B ();

    void read_height ();

    axis (Ultrasonic &ultra_object1, Ultrasonic &ultra_object2);

    double check_axis_orientary ();

    void get_status();

    ~axis ();

};
