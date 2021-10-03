#pragma once
#include "stateobj.h"



class CCoreState : public CStateObj {
  public:
  
  CCoreState() { _name="CORE"; };
  ~CCoreState() {};


  void setup();
  
};


   
