#include "system_datarequest.h"
#include <messages.h>
#include "cubesat.h"

void CDataRequest::loop() {
  writeconsoleln("DataRequest Loop");
 //Pumps messages through the system
 //moveData();


 CMsg m;
 m.setSYS("GPS");
 m.setACT("OUTPUT");
 addMessageList(m);
}

void CDataRequest::moveData() {
	CMessages* pmsgs=getMessages();


	//for (std::list<CMsg>::iterator it = pmsgs->DataList.begin(); it != pmsgs->DataList.end(); ++it) {
 //for (auto it = pmsgs->DataList.begin(); it != pmsgs->DataList.end(); ++it) {
	//	CMsg m = *it;
  for(auto m:pmsgs->DataList){  
		pmsgs->TransmitList.push_back(m);

		//parameters["TIME"]
		//if (cmsg.parameters["CID"]==m.CID()
	}
}
