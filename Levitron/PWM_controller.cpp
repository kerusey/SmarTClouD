#include "PWM_controller.h"

unsigned int convert_byte_to_percent () {
  return int(analog_power/255*100);
}

int convert_percent_to_byte () {
  return int(percent_power*100/255);
}

void set_analog (byte _analog_power) {

  analog_power = _analog_power;
  percent_power = convert_analog_to_percent(_analog_power);
  current_voltage = percent/20;
  analogWrite(pwm_pin, analog_power);
  
}

byte get_percent () { 
  return percent_power;
}

byte get_analog () {
  return analog_power;
}

void set_percent (byte _percent_power) {
  percent_power = _percent_power(
  analog_power = convert_analog_to_percent();
  current_voltage = power_percent / 20;
  analogWrite(pwm_pin, analog_power);
}

void buck (byte steps = 1) {
  set_percent(get_percent() - steps);
}

void boost (byte steps = 1) {
  set_percent (get_percent() + steps);
}

pwm_coil (byte _set_pin) {
  pwm_pin = _set_pin;
  set_analog(default_analog);
}

~pwm_coil () {}
