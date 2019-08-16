#pragma once

#define start_resistance 202.02
#define const_delta_resistance 101.01

class resisto_coil {

  int UD;
  int INC;
  int CS;  // ports for resistor pci

  double resistance;

public:

  resisto_coil (int _UD, int _INC); // my_ input must be constant !!!

  void boot ();

  double get_pot_resistance ();

  void change_coil_resistance (int res);

  void buck (unsigned int _step = 1);

  void boost (unsigned int _step = 1);

  void set_new_resistance(unsigned int _res);

  ~resisto_coil ();

};
