#include "Status.h"

/*
bool local_protect (resisto_coil &pot) {  //  this func used to be a defender from Short circuit
  unsigned int Icurrent = voltage/pot.get_pot_resistance() + voltage/(additional_resistor + coil_resistance);
  if (voltage/pot.get_pot_resistance() >= max_potentiometer_current || Icurrent >= max_coil_current)
    return true;
}
bool st::global_protect (resisto_coil &pot1, resisto_coil &pot2, resisto_coil &pot3, resisto_coil &pot4) {
   return (local_protect (pot1) + local_protect (pot2) + local_protect (pot3) + local_protect (pot4));
} */ ///. KerPatch-4 and older

bool st::global_protect (pwm::coil &magnet_object1, pwm::coil &magnet_object2, pwm::coil &magnet_object3, pwm::coil &magnet_object4) {
  return magnet_object1.get_voltage()/coil_resistance + magnet_object2.get_voltage()/coil_resistance + magnet_object3.get_voltage()/coil_resistance + magnet_object4.get_voltage()/coil_resistance < max_total_amp;
} ///. KerPatch-5 and newer

size_t st::Status::get_status() { return NT_STATUS; }

bool st::Status::NT_critical() { return NT_STATUS == 0? true:false; }

void st::Status::resolve_status () {
if (global_protect()) NT_STATUS = 0;
  else if (ax::get_height() >= max_height || ax::get_height() <= min_height) NT_STATUS = 1;
  else if (Axis::check_left_side() || Axis::check_right_side())
NT_STATUS = 2;
  else NT_STATUS = 3;
}

st:Status::Status() { resolve_status(); }

st::Status::~Status() {}
