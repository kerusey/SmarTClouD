/*
  tipization : NT_STATUS == 0 - critical stop
               NT_STATUS == 1 - deviation of default height (normally about 2-3 CM)
               NT_STATUS == 2 - incline of the magnet body in X/Y axis
               NT_STATUS == 3 - perfect (may not be written in case of unrealistic)
*/
#pragma once
#include "Ports.h"
#include "PWM_controller.h"
#include "Axis.h"

// #define max_potentiometer_current 0.750  ///. KerPatch-4 and older

#define max_coil_current 11.0   // amps
#define max_total_amp 6.0
#define coil_resistance 0.37625
#define voltage 5.0          // default voltage

namespace st {

  /*
  bool local_protect (resisto_coil &pot);
  bool global_protect (resisto_coil &pot1, resisto_coil &pot2, resisto_coil &pot3, resisto_coil &pot4);
  */
  ///. KerPatch-4 and older

  bool global_protect (pwm::coil &magnet_object1, pwm::coil &magnet_object2, pwm::coil &magnet_object3, pwm::coil &magnet_object4);
  ///. KerPatch-5 and newer

  class Status {
    int NT_STATUS;  // NOTADRIVERHANDLE

  public:
    Stratus();
    bool critical();
    int get_status();
    ~Status();
  }

}
