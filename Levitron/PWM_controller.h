#pragma once 
#define default_analog 127

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

class pwm_coil {

  byte analog_power;
  double current_voltage;
  size_t percent_power;
  size_t pwm_pin;

  size_t convert_analog_to_percent ();
  byte convert_percent_to_analog ();

public:

  void set_analog (byte _current_byte);
  void set_percent (int _percent_power);
  size_t get_percent ();
  byte get_analog ();
  double get_voltage();
  
  void buck (size_t steps = 1);
  void boost (size_t steps = 1);
  
  pwm_coil (size_t _pwm_pin);

  ~pwm_coil ();
};
