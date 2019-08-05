#pragma once

#define _CS 9   // CS port
#define const_resistance 10.0

#define const_delta_resistance 3.906

class resisto_coil {

  int sdi;
  int clk;
  int cs;  // ports for resistor pci

  float resistance;

public:

  resisto_coil (int _sdi, int _clk); // my_ input must be constant !!!

  void boot ();

  double coil_resistance ();

  void change_coil_resistance (int res);

  void set_new_resistance (unsigned int _res);

  ~resisto_coil ();
  
};
