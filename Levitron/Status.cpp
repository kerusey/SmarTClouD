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

// now creating a 4 megnetic coil objects, been controlled by PWM controllers; **

bool hall_check () { // checks "Hall exeption"
  if (digitalRead(HallS_D1) == LOW || digitalRead(HallS_D2) == LOW || digitalRead(HallS_D3) == LOW || digitalRead(HallS_D4) == LOW)
    return true;
  return false;
}

size_t st::Status::get_status() { return NT_STATUS; }

bool st::Status::NT_critical() { return NT_STATUS == 0? true:false; }

void st::Status::resolve_status () {
if (!global_protect()) NT_STATUS = 0;
  else if (ax::height >= 2*critical_height || ax::height <= critical_height) NT_STATUS = 1;
  else NT_STATUS = 2;
}

st::Status::Status() { resolve_status(); }

st::Status::~Status() {}

bool st::Status::global_protect () {
  st::Status::resolve_status();
//  return (magnet_object1.get_voltage()/coil_resistance + magnet_object2.get_voltage()/coil_resistance + magnet_object3.get_voltage()/coil_resistance + magnet_object4.get_voltage()/coil_resistance < max_total_amp) || !NT_critical();
} ///. KerPatch-5 and newer
