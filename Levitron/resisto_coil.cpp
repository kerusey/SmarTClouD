#include "resisto_coil.h"

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif


resisto_coil::resisto_coil (int _sdi, int _clk) { // _input must be constant !!!
  
  resistance = const_resistance;
  sdi = _sdi;
  clk = _clk;
  cs = _CS;

}

void resisto_coil::boot () {
  pinMode(sdi, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);
}

double resisto_coil::coil_resistance () { return resistance; }

void resisto_coil::change_coil_resistance (int res) {

  digitalWrite(cs, HIGH);
  digitalWrite(sdi, HIGH);
  digitalWrite(clk, LOW);

  delayMicroseconds(1);

  digitalWrite(cs, LOW);

  delayMicroseconds(1);

  digitalWrite(sdi, LOW);

  delayMicroseconds(1);

  for (size_t i = 0 ; i < 2 ; ++i) {
    digitalWrite (clk, LOW);
    digitalWrite (clk, HIGH);
  }

  for (size_t i = 7 ; i >= 0 ; --i) {
    digitalWrite (clk, LOW);
    int bt = bitRead(res, i);

    if (bt == 1) digitalWrite (sdi, HIGH);
    else digitalWrite (sdi, LOW);

    digitalWrite (clk, HIGH);
  }
  digitalWrite (cs, HIGH);
}

void resisto_coil::set_new_resistance(unsigned int _res) { change_coil_resistance(int((_res - resistance/const_delta_resistance))); }

resisto_coil::~resisto_coil () {}
