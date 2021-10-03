#pragma once
#include "stateobj.h"


class CPhoneState: public CStateObj {
public:
  CPhoneState() {
  _name="PhoneState";
    //add some items to the map
    //availablesystems["LIGHT"] = true;
    //availablesystems["IMU"] = true;
  };
  ~CPhoneState() {};
  void stateMsg(CMsg &msg){_statemsg=msg;};
  void setup() {};

void enter() { CStateObj::enter();writeconsole("Enter Phone"); }
  void exit() { CStateObj::exit();writeconsole("Exit Phone"); }


};
