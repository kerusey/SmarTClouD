#include "Ultrasonic.h"

#define const_alpha 30

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
