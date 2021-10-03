#pragma once
#include <defs.h>

#ifdef TTGO
#include "systemobject.h"
#include <string>
#include <TinyGPS++.h>
#include <axp20x.h>

class CGPS :public CSystemObject {
  TinyGPSPlus gpsl;
  AXP20X_Class axp;

  float latitude=0.0;
  float longitude=0.0;
  float altitude=0.0;
  char SIV=' ';
  int Yr=0;
  int Mon=0;
  int Day=0;
  int Hr=0;
  int Min=0;
  int Sec=0;
  long Speed=0;
public:

  CGPS();
  CGPS(CMsg &msg);
  ~CGPS() {
    writeconsole("GPS destroyed");
  }
  void setup();
  void loop();
  void init();
  void Output();
  void smartDelay(unsigned long ms);
  CMsg fillData();
 
};

#endif
