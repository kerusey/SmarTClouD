#include "Pwm_coil.h"

size_t Pwm_coil::convert_analog_to_percent () { return size_t(analog_power/255*100); }
int Pwm_coil::convert_percent_to_analog () { return int(percent_power*100/255); }

size_t Pwm_coil::get_percent () { return percent_power; }
int Pwm_coil::get_analog () { return analog_power; }
double Pwm_coil::get_voltage () { return current_voltage; }

void Pwm_coil::set_analog (int _analog_power) {
  analog_power = _analog_power;
  percent_power = convert_analog_to_percent();
  current_voltage = percent_power/20;
  analogWrite(pwm_pin, analog_power);
}

void Pwm_coil::set_percent (int _percent_power) {
  percent_power = _percent_power;
  analog_power = convert_analog_to_percent();
  current_voltage = percent_power/ 20;
  analogWrite(pwm_pin, analog_power);
}

void Pwm_coil::buck (size_t steps = 1) {
  set_percent(get_percent() - steps);
}

void Pwm_coil::boost (size_t steps = 1) {
  set_percent (get_percent() + steps);
}

Pwm_coil::Pwm_coil (size_t _pwm_pin, size_t _serial) {
  pwm_pin = _pwm_pin;
  pinMode(pwm_pin, OUTPUT);
  Serial.begin(_serial);
  if (Serial.available() > 0)
    set_analog(default_analog);
}

Pwm_coil::~Pwm_coil () {}
