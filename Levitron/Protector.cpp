#include "Protector.h"
// #include "resisto_coil.h"
#include "Ports.h"
/*
bool local_protect (resisto_coil &pot) {  //  this func used to be a defender from Short circuit
  unsigned int Icurrent = voltage/pot.get_pot_resistance() + voltage/(additional_resistor + coil_resistance);
  if (voltage/pot.get_pot_resistance() >= max_potentiometer_current || Icurrent >= max_coil_current)
    return true;
}

bool global_protect (resisto_coil &pot1, resisto_coil &pot2, resisto_coil &pot3, resisto_coil &pot4) {
   return (local_protect (pot1) + local_protect (pot2) + local_protect (pot3) + local_protect (pot4));
} */ // KerPatch-4 and lower

bool global_protect (pwm::coil &magnet_object1, pwm::coil &magnet_object2, pwm::coil &magnet_object3, pwm::coil &magnet_object4) {
  return magnet_object1.get_voltage()/coil_resistance + magnet_object2.get_voltage()/coil_resistance + magnet_object3.get_voltage()/coil_resistance + magnet_object4.get_voltage()/coil_resistance > max_total_amp;
} // KerPatch-5 
