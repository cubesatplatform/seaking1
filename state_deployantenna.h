#pragma once
#include "stateobj.h"


class CDeployAntennaState: public CStateObj {
public:
	CDeployAntennaState() {
  _name="Deploy";
		//add some items to the map
		//availablesystems["LIGHT"] = true;
		//availablesystems["IMU"] = true;
	};
	~CDeployAntennaState() {};
  void stateMsg(CMsg &msg){_statemsg=msg;};
	void setup() {};

  void enter() { CStateObj::enter();writeconsole("Enter Deploy Antenna"); }
  void exit() { CStateObj::exit();writeconsole("Exit Deploy Antenna"); }

};
