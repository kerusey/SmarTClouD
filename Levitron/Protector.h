#pragma once

#include "resisto_coil.h"
#include "Ports.h"
#include "PWM_controller.h"

// #define max_potentiometer_current 0.750  //

#define max_coil_current 11.0   // amps
#define max_total_amp 6.0
#define coil_resistance 0.37625
#define voltage 5.0          // default voltage

// #define potentiometer_resistance 10000.0 //
// #define potentiometer_steps 100       // (//) you may resad datasheet of your potentiometer
// #define additional_resistor 220.0      // resistor that helps aviod short circuit

// bool local_protect (resisto_coil &pot);

bool global_protect (pwm_coil &magnet_object1, pwm_coil &magnet_object2, pwm_coil &magnet_object3, pwm_coil &magnet_object4);
