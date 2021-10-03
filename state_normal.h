#pragma once
#include "stateobj.h"


class CNormalState : public CStateObj {  //Normal let everything through
private:

public:
	CNormalState() {
		//add some items to the map
   _name="Normal";
	availablesystems["LIGHT"] = true;
  availablesystems["LIGHTRED"] = true;
	availablesystems["IMU"] = true;
  availablesystems["GPS"] = true;
  availablesystems["DATAREQUEST"] = true;
  availablesystems["PWM1"] = true;
  availablesystems["PWM2"] = true;
  availablesystems["PWM3"] = true;
		
	};
	~CNormalState() {};

	void setup() {};
	void enter() { CStateObj::enter();writeconsole("Enter Normal"); }
	void exit() { CStateObj::exit();writeconsole("Exit Normal"); }
	

};
