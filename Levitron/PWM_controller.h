#define default_voltage 3.3 // volts 
#define const_delta_voltage 0.1 // step
#define default_step 127

class pwm_coil {

  byte power_byte;
  double current_voltage;
  byte power_percent;
  byte PWM_pin;

  byte convert_byte_to_percent ();
  byte convert_percent_to_byte ();

public:
  void set_analog (double _current_voltage = default_voltage, unsigned int _current_percent = NULL, int _current_byte = NULL);
  void buck (double _const_delta_voltage = const_delta_voltage);
  void boost (double _const_delta_voltage = const_delta_voltage);
  pwm_coil ();

  ~pwm_coil ();
};
