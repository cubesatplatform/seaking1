#pragma once
#include "stateobj.h"


class CNormalState : public CStateObj {  //Normal let everything through
private:

public:
	CNormalState() {
		//add some items to the map
   _name="Normal";
	
  availablesystems["GPS"] = true;
  availablesystems["DATAREQUEST"] = true;
		
	};
	~CNormalState() {};

	void setup() {};
	void enter() { CStateObj::enter();writeconsole("Enter Normal"); }
	void exit() { CStateObj::exit();writeconsole("Exit Normal"); }
	

};
