#pragma once
#include <list>
#include <systemobject.h>
  

class CSystemMgr:public CSystemObject{
  
std::list<CMsg> ToDoList;      
std::list<CMsg> DoneList;      

  
public:
  CSystemMgr() {Name("SYSTEMMGR");_forever=true;_INTERVAL=30000;};    
  ~CSystemMgr();

  bool init();
  void setup();
  void loop();
  void chkClocks(){writeconsoleln("Checking Clocks & Counters...");};
  void chkRadio(){writeconsoleln("Checking Radio...");};
  void chkCurrentState(){writeconsoleln("Checking Current...");};
  void chkAllStates(){writeconsoleln("Checking All States...");};
  void chkTemperature(){writeconsoleln("Checking Temps...");};
  void chkBattery(){writeconsoleln("Checking Battery...");};
  void chkRotation();
  void chkCoreSystems(){writeconsoleln("Checking CoreSystems...");};
  void chkMessages(){writeconsoleln("Checking Messages...");};
  void stateLowPower(){setState("LOWPOWER");};
  void stateReallyLowPower(){setState("LOWPOWER");};
  void stateDetumble(){setState("DETUMBLE");};
  
  void sendHealth(){writeconsoleln("Send Health...");};
  void sendBeacon(){writeconsoleln("Send Beacon...");};
  void sendError(std::string str){};
  void RESET(){};

  void setState(const char *str="LOWPOWER");
};













  
