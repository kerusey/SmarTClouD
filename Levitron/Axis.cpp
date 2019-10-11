#include "Axis.h"

void ax::Axis::read_L1 () {
  L1_dist = ultra_object1->read();
}

void ax::Axis::read_L2 () {
  L2_dist = ultra_object2->read();
}

ax::Axis::axis(Ultrasonic &ultra_object1, Ultrasonic &ultra_object2) {
  read_L1();
  read_L2();

} // constructor

bool ax::Axis::check_right_half () { // returns true if not inclined to right
  if (!global_protect() || !st::get_status())
    return L1_dist <= sqrt ( height * height + sqr ((baseline - magnet_body_lenght) / 2));
}

bool ax::Axis::check_left_half () { // returns true if not inclined to left
  if (!global_protect() || !st::get_status())
    return L2_dist <= sqrt ( height * height + sqr ((baseline - magnet_body_lenght) / 2));
}

int ax::Axis::check_axis_orientary () { // returns  abstract points of incline (positive - to right ; negative - to left)
  if (!check_right_half()) return 1;
  else return -1;
}

ax::Axis::~axis () {}

void ax::read_height () {
  height = ax::ultra_height->read();
}  // height is unique (not common for each class)
