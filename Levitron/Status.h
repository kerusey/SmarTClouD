/*
  tipization : NT_STATUS == 0 - critical stop
               NT_STATUS == 1 - deviation of default height (normally about 2-3 CM)
               NT_STATUS == 2 - incline of the magnet body in X/Y axis
               NT_STATUS == 3 - perfect (may not be written in case of unrealistic)
*/
#pragma once
#include "Ports.h"
#include "Pwm_coil.h"
#include "Axis.h"
#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

// #define max_potentiometer_current 0.750  ///. KerPatch-4 and older

// magnet objects initialization

Pwm_coil magnet_object1 (PWM_pin1, SERIAL1),
         magnet_object2 (PWM_pin2, SERIAL2), // for X axis

         magnet_object3 (PWM_pin3, SERIAL3),
         magnet_object4 (PWM_pin4, SERIAL4); // for Y axis

// magnet objects initialization

#define max_coil_current 11.0   // amps
#define max_total_amp 6.0
#define coil_resistance 0.37625
#define voltage 5.0          // default voltage
#define critical_height 7.0 // (CM)

namespace st {
  /*
  bool local_protect (resisto_coil &pot);
  bool global_protect (resisto_coil &pot1, resisto_coil &pot2, resisto_coil &pot3, resisto_coil &pot4);
  */
  ///. KerPatch-4 and older

  class Status {
    int NT_STATUS;  // NOTADRIVERHANDLE

  public:
    Status();
    bool NT_critical();
    size_t get_status();
    void resolve_status ();
    bool global_protect (); ///. KerPatch-5 and newer
    ~Status();
  };

};
