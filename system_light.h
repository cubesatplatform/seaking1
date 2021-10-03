#pragma once
#include <systemobject.h>
#include <pwmpin.h>

//
//This moves a certain type of data to TransmitList
//
class CLight :public CSystemObject {

public:
  CLight():CSystemObject() {init(); }
  CLight(CMsg &msg) {init(); _cmsg = msg; }
  ~CLight();
  void init(){Name("LIGHT");_INTERVAL=5;}


   
  void setup();
  void loop();

};
