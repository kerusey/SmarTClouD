#pragma once

#include "Ports.h"
#include "PWM_controller.h"

// #define max_potentiometer_current 0.750  //

#define max_coil_current 11.0   // amps
#define max_total_amp 6.0
#define coil_resistance 0.37625
#define voltage 5.0          // default voltage

bool global_protect (pwm::coil &magnet_object1, pwm::coil &magnet_object2, pwm::coil &magnet_object3, pwm::coil &magnet_object4);
