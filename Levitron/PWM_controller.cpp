#include "PWM_controller.h"

size_t pwm::coil::convert_analog_to_percent () { return size_t(analog_power/255*100); }
int pwm::coil::convert_percent_to_analog () { return int(percent_power*100/255); }

size_t pwm::coil::get_percent () { return percent_power; }
int pwm::coil::get_analog () { return analog_power; }
double pwm::coil::get_voltage () { return current_voltage; }

void pwm::coil::set_analog (int _analog_power) {
  analog_power = _analog_power;
  percent_power = convert_analog_to_percent();
  current_voltage = percent_power/20;
  analogWrite(pwm_pin, analog_power);
}

void pwm::coil::set_percent (int _percent_power) {
  percent_power = _percent_power;
  analog_power = convert_analog_to_percent();
  current_voltage = percent_power/ 20;
  analogWrite(pwm_pin, analog_power);
}

void pwm::coil::buck (size_t steps = 1) {
  set_percent(get_percent() - steps);
}

void pwm::coil::boost (size_t steps = 1) {
  set_percent (get_percent() + steps);
}

pwm::coil::coil (size_t _pwm_pin, size_t _serial) {
  pwm_pin = _pwm_pin;
  pinMode(pwm_pin, OUTPUT);
  Serial.begin(_serial);
  if (Serial.available() > 0)
    set_analog(default_analog);
}

pwm::coil::~coil () {}
