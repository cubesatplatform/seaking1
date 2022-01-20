#pragma once
#include <defs.h>


#include "systemobject.h"
#include <string>

class CExample :public CSystemObject {
  long lcount=0;

public:

  CExample();
  void setup();
  void loop();
};
