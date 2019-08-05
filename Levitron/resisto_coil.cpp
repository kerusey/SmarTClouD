#include "resisto_coil.h"

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif



resisto_coil::resisto_coil (int _UD, int _INC) { // _input must be constant !!!
  
  resistance = const_resistance;
  UD = _UD;
  INC = _INC;
  CS = _CS;

}

void resisto_coil::boot () {
  pinMode(INC, OUTPUT);
  pinMode(UD, OUTPUT);
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
}

double resisto_coil::coil_resistance () { return resistance; }

void resisto_coil::boost (unsigned int _steps) {                            
  for (int i = 0 ; i < _steps ; ++i) {
    
    digitalWrite(UD, HIGH);             
    
    digitalWrite(INC, HIGH);            
    
    digitalWrite(CS, LOW);              
    
    delayMicroseconds(1);               
    
    digitalWrite(INC, LOW);             
    
    delayMicroseconds(1);
    
    digitalWrite(INC, HIGH);
    
    delayMicroseconds(1);
  //digitalWrite(INC, LOW);            
    
    digitalWrite(CS, HIGH);
  }
}

void resisto_coil::buck(unsigned int _step) {
  for (int i = 0 ; i < _step ; ++i) {
    
    digitalWrite(UD, LOW);
    
    digitalWrite(INC, HIGH);
    
    digitalWrite(CS, LOW);
    
    delayMicroseconds(1);
    
    digitalWrite(INC, LOW);
    
    delayMicroseconds(1);
    
    digitalWrite(INC, HIGH);
    
    delayMicroseconds(1);
        
    digitalWrite(CS, HIGH);
  }
}


void resisto_coil::set_new_resistance(unsigned int _res) { change_coil_resistance(int((_res - resistance/const_delta_resistance))); }

resisto_coil::~resisto_coil () {}
