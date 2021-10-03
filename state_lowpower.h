#pragma once
#include "stateobj.h"


class CLowPowerState : public CStateObj {
public:
	CLowPowerState() {
		//add some items to the map
		//availablesystems["LIGHT"] = true;
		//availablesystems["IMU"] = true;
	};
	~CLowPowerState() {};

	void setup() {};
void enter() { CStateObj::enter();writeconsole("Enter Low Power"); }
  void exit() { CStateObj::exit();writeconsole("Exit Low Power"); }

};
