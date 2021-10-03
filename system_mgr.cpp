#include "system_mgr.h"
#include <messages.h>


    
  CSystemMgr::~CSystemMgr(){}

  
  
  bool CSystemMgr::init(){
   
   setState("PLAY");
  
}


void CSystemMgr::setup(){init();}



  void CSystemMgr::loop(){
  chkRadio();
  chkCurrentState();
  chkAllStates();
  chkTemperature();
  chkBattery();
  chkCoreSystems();
  chkMessages();
  
  sendHealth();
  sendBeacon();
  }


void CSystemMgr::setState(const char *str){
  CMsg msg;
  msg.Parameters["STATE"]=str;
  //newState(msg);
  CMessages* pM=getMessages();
  pM->newMessage(msg);    //Send message to system to have it change state
}
