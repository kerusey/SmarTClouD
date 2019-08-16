#pragma once

#include "resisto_coil.h"
#include "Ports.h"

#define max_potentiometer_current 0.750  //
#define max_coil_current 11.0   // amps
#define coil_resistance 0.37625
#define voltage 5.0          // default arduino voltage
#define potentiometer_resistance 10000.0 //
#define potentiometer_steps 100       // (//) you may resad datasheet of your potentiometer
#define additional_resistor 220.0      // resistor that helps aviod short circuit

bool local_protect (resisto_coil &pot);

bool global_protect (resisto_coil &pot1, resisto_coil &pot2, resisto_coil &pot3, resisto_coil &pot4);
