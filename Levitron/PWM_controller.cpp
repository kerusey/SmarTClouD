#include "PWM_controller.h"

unsigned int convert_byte_to_percent () {
  
}

int convert_percent_to_byte () {

}

void set_voltage (double _current_voltage = default_voltage, unsigned int _current_percent = NULL, int _current_byte = NULL);
void buck (double _const_delta_voltage = const_delta_voltage);
void boost (double _const_delta_voltage = const_delta_voltage);
pwm_coil ();

~pwm_coil ();
