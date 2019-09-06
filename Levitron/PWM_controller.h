#define default_voltage 3.3 // volts 
#define const_delta_voltage 0.1 // step
#define default_step 127

class pwm_coil {

  int power_byte;
  double current_voltage;
  unsigned int power_percent;

  unsigned int convert_byte_to_percent ();
  int convert_percent_to_byte ();

public:
  void set_voltage (double _current_voltage = default_voltage, unsigned int _current_percent = NULL, int _current_byte = NULL);
  void buck (double _const_delta_voltage = const_delta_voltage);
  void boost (double _const_delta_voltage = const_delta_voltage);
  pwm_coil ();

  ~pwm_coil ();
};
