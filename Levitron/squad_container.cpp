#include "squad_container.h"

void squad_container::import_sq (double _sm1, double _sm2, double _sm3, double _sm4){
  squad_member1 = _sm1;
  squad_member2 = _sm2;
  squad_member3 = _sm3;
  squad_member4 = _sm4;
}

squad_container::squad_container (double _sm1, double _sm2, double _sm3, double _sm4) { import_sq(_sm1, _sm2, _sm3, _sm4); }

void squad_container::export_sq (double &_sm1, double &_sm2, double &_sm3, double &_sm4){
  _sm1 = squad_member1;
  _sm2 = squad_member2;
  _sm3 = squad_member3;
  _sm4 = squad_member4;
}

squad_container::~squad_container () {} 
