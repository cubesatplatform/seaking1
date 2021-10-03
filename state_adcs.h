#pragma once
#include "stateobj.h"


class CADCSState : public CStateObj {
public:
	CADCSState() {
    _name="ADCS";
		//add some items to the map
		availablesystems["LIGHT"] = true;
		availablesystems["IMU"] = true;
	};
	~CADCSState() {};

	void setup() {};
  void stateMsg(CMsg &msg){_statemsg=msg;};
  void enter() { CStateObj::enter();writeconsole("Enter ADCS"); }
  void exit() { CStateObj::exit();writeconsole("Exit ADCS"); }
	
};
