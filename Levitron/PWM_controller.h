#pragma once 
#define default_analog 127

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#define SERIAL1 9600
#define SERIAL2 12000
#define SERIAL3 16603
#define SERIAL4 131312

namespace pwm {
  class coil {
  
    int analog_power;
    double current_voltage;
    size_t percent_power;
    size_t pwm_pin;
  
    size_t convert_analog_to_percent ();
    int convert_percent_to_analog ();
  
  public:
  
    void set_analog (int _current_byte);
    void set_percent (int _percent_power);
    size_t get_percent ();
    int get_analog ();
    double get_voltage();
    
    void buck (size_t steps = 1);
    void boost (size_t steps = 1);
    
    coil (size_t _pwm_pin, size_t _serial);
  
    ~coil ();
  };
};
