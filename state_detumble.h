#pragma once
#include "stateobj.h"


class CDetumbleState : public CStateObj {
public:
  CDetumbleState();
  ~CDetumbleState();

  void setup();
  void stateMsg(CMsg &msg);
  void enter();
  void exit();
  
};
