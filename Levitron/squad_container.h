#pragma once

class squad_container {  // used here to contain resistance before hall_check func change it (uleless in futuere)

  double squad_member1;
  double squad_member2;
  double squad_member3;
  double squad_member4;

public:

  void import_sq (double _sm1, double _sm2, double _sm3, double _sm4); // import data to container

  squad_container (double _sm1, double _sm2, double _sm3, double _sm4);

  void export_sq (double &sm1, double &sm2, double &sm3, double &sm4); // export data from container

  ~squad_container ();

};
