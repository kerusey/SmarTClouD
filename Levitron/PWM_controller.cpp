#include "PWM_controller.h"

size_t pwm_coil::convert_analog_to_percent () { return size_t(analog_power/255*100); }
byte pwm_coil::convert_percent_to_analog () { return byte(percent_power*100/255); }

size_t pwm_coil::get_percent () { return percent_power; }
byte pwm_coil::get_analog () { return analog_power; }
double pwm_coil::get_voltage () { return current_voltage; }

void pwm_coil::set_analog (byte _analog_power) {
  analog_power = _analog_power;
  percent_power = convert_analog_to_percent();
  current_voltage = percent_power/20;
  analogWrite(pwm_pin, analog_power);
}

void pwm_coil::set_percent (int _percent_power) {
  percent_power = _percent_power;
  analog_power = convert_analog_to_percent();
  current_voltage = percent_power/ 20;
  analogWrite(pwm_pin, analog_power);
}

void pwm_coil::buck (size_t steps = 1) {
  set_percent(get_percent() - steps);
}

void pwm_coil::boost (size_t steps = 1) {
  set_percent (get_percent() + steps);
}

pwm_coil::pwm_coil (size_t _pwm_pin) {
  pwm_pin = _pwm_pin;
  set_analog(default_analog);
}

pwm_coil::~pwm_coil () {}
