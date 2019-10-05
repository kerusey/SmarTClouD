#include "Axis.h"

void Axis::read_L1 () {
  L1_dist = ultra_object1->read();
}

void Axis::read_L2 () {
  L2_dist = ultra_object2->read();
}

Axis::axis(Ultrasonic &ultra_object1, Ultrasonic &ultra_object2) {
  read_L1();
  read_L2();

} // constructor

bool Axis::check_right_half () { // returns true if not inclined to right
  if (!global_protect() || !st::get_status())
    return L1_dist <= sqrt(sqr(L1_dist * cos(const_alpha)) + sqr(height))
}

bool Axis::check_left_half () { // returns true if not inclined to left
  if (!global_protect() || !st::get_status())
    return L2_dist <= sqrt(sqr(L2_dist * cos(const_alpha)) + sqr(height))
}

int Axis::check_axis_orientary () { // returns  abstract points of incline (positive - to right ; negative - to left)
  int points = 0;
  if (sqrt ( height * height + sqr ( L2_dist * cos ( const_alpha ) ) ) - L2_dist) points--;
  if (sqrt ( height * height + sqr ( L1_dist * cos ( const_alpha ) ) ) - L1_dist) points++;
  return points;
}

Axis::~axis () {}

void ax::read_height () {
  height = ax::ultra_height->read();
}  // height is unique (not common for each class)
