#define default_analog 127

class pwm_coil {

  byte power_byte;
  double current_voltage;
  byte power_percent;
  byte pwm_pin;

  byte convert_byte_to_percent ();
  byte convert_percent_to_byte ();

public:

  void set_analog (byte _current_byte);

  void buck (byte steps);

  void boost (byte steps);

  pwm_coil ();

  ~pwm_coil ();
};
