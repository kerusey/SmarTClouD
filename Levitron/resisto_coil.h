#pragma once

#define const_resistance 202.0202
#define const_delta_resistance 101.0101

#define UD_1 7
#define INC_1 8

#define UD_2 35
#define INC_2 36

#define UD_3 58
#define INC_3 59

#define UD_4 70
#define INC_4 71

#define _CS 9   // CS port


class resisto_coil {

  int UD;
  int INC;
  int CS;  // ports for resistor pci

  float resistance;

public:

  resisto_coil (int _UD, int _INC); // my_ input must be constant !!!

  void boot ();

  double coil_resistance ();

  void change_coil_resistance (int res);

  void buck (unsigned int _step = 1);

  void boost (unsigned int _step = 1);

  void set_new_resistance(unsigned int _res);
  
  ~resisto_coil ();
  
};
