#pragma once
#include <systemobject.h>

//
//This moves a certain type of data to TransmitList
//
class CDataRequest :public CSystemObject {
	
public:
	CDataRequest():CSystemObject() {init(); }
	CDataRequest(CMsg &msg) { _cmsg = msg;init(); }
	~CDataRequest() {}
  void init(){Name("DATAREQUEST");_forever = true;_INTERVAL=5000;}
	void setup() { setState("PLAY"); }
	void loop();
	void moveData();
 
};
