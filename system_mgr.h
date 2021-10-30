#pragma once
#include <msg.h>
#include <funcs.h>

#include <list>
#include <systemobject.h>
#include <fhmotor.h>
#include "SparkFun_BNO080_Arduino_Library.h"
#include <radio.h>
#include <arduino.h>

#include <string>
#include <mdrive.h>
#include <unordered_set>
  


#if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)
   // #include <pinDefinitions.h>
/*
    #define IMU_OBC_NSS PinNameToIndex(PB_4)
    #define IMU_OBC_RST PinNameToIndex(PI_14)
    #define IMU_OBC_INT PinNameToIndex(PI_15)
    #define IMU_OBC_WAKE PinNameToIndex(PB_3)

*/
    #define IMU_OBC_NSS PinNameToIndex(PJ_8)
    #define IMU_OBC_RST PinNameToIndex(PI_14)
    #define IMU_OBC_INT PinNameToIndex(PI_15)
    #define IMU_OBC_WAKE PinNameToIndex(PJ_9)

#else
    #define TTGO
    typedef int PinName; 
#endif




class CSystemMgr:public CSystemObject{
  
std::list<CMsg> ToDoList;      
std::list<CMsg> DoneList;      
int _channel=0;
const int freq = 5000;
const int resolution = 8;




  std::map<std::string, PinName> Pins;
  std::unordered_set<std::string> pwmPins;

  
public:
  CSystemMgr() {Name("SYSTEMMGR");_forever=true;_INTERVAL=30000;};    
  ~CSystemMgr();

  bool init();
  void setup();
  void loop();

  void callCustomFunctions(CMsg &msg);
  void powerLevel(CMsg &msg);
  void chkClocks(){writeconsoleln("Checking Clocks & Counters...");};
  void chkRadio(){writeconsoleln("Checking Radio...");};
  void chkCurrentState(){writeconsoleln("Checking Current...");};
  void chkAllStates(){writeconsoleln("Checking All States...");};
  void chkTemperature(){writeconsoleln("Checking Temps...");};
  void chkBattery(){writeconsoleln("Checking Battery...");};
  void chkRotation(){};
  void chkCoreSystems(){writeconsoleln("Checking CoreSystems...");};
  void chkMessages(){writeconsoleln("Checking Messages...");};

  
  void stateLowPower(){newState("LOWPOWER");};
  void stateReallyLowPower(){newState("LOWPOWER");};
  void stateDetumble(){newState("DETUMBLE");};
  
  void sendHealth(){writeconsoleln("Send Health...");};
  void sendBeacon(){writeconsoleln("Send Beacon...");};
  void sendError(std::string str){};
  
  void RESET(){};

  void loopWire(TwoWire *wire);
  void enableI2C();
  void SendCmd(std::string str);
  void newState(const char *str="LOWPOWER");
  
  void burn();
  void phone();
  void pinsOn();
  void pinsOff();
  void setupIMUSPI();
  void setupIMUI2C(TwoWire *wire);
  void displayCMDs();
  void initPins();
  void sendSerial(const char* cmd);
};













  
