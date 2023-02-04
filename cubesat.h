#pragma once

#include "defs.h"
#include <csfilenames.h>

#include <msgpump.h>
#include <stateobj.h>


#include <state_detumble.h>
#include <state_deployantenna.h>
#include <state_payload.h>
#include <state_adcs.h>
#include <state_lowpower.h>
#include <system_reactionwheel.h>
#include <system_magtorquer.h>
#include <system_temperature.h>
#include <mdrive.h>
#include <fhmotor.h>
#include <system_imu.h>
#include <radio.h>
#include <kb.h>

#include <system_mgr.h>
#include <scheduler.h>
#include <system_irarray.h>
#include <phone.h>



#if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)   
  #include <ceps.h>  
#else
  #include <system_gps.h>
#endif  




class CSatellite:public CStateObj {
public:
  int _restartcount=0;  
	long lcount=0;

  CADCSState _state_adcs;     
  CStateObj _state_core;
  CDeployAntennaState _state_deployantenna;  
  CDetumbleState _state_detumble;  
  CLowPowerState _state_lowpower;     
  CStateObj _state_normal;          
  CPayloadState _state_payload;
    
  CKeyboard _keyboard;

   
 // CEPS _power;
  CIMU _IMUSPI;
  CIMU _IMUI2C;     
 
  CIRArray _ir_X1,_ir_X2,_ir_Y1,_ir_Y2,_ir_Z1,_ir_Z2;
  
  CMagTorquer _magneTorquers;
  
  CMsgPump _msgPump;
  
  CMDrive _magX;
  CMDrive _magY;
  CMDrive _magZ;
  
  CSystemMgr _manager;
/*
  CMotorController _motorX;
  CMotorController _motorY;
  CMotorController _motorZ;
*/
  CPhone _phone;    

  CRadio _radio;   
  #if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7) 
  CRadio _radio2; 
  #else 
    #define _radio2 _radio  
    CGPS _gps;
  #endif  


  //CRW _reactionWheels;
  
  CScheduler _scheduler;
  
  CTemperatureObject _tempX1,_tempX2,_tempY1,_tempY2,_tempZ1,_tempZ2, _tempOBC;
  
	CSatellite();

	//void deleteState(CMsg &msg);
  //void addState(CMsg &msg);
  void createState(CMsg &msg);
  void changeState(CMsg &msg);
  
  void newMsg(CMsg &msg);
 
	void setup();    
  void loop();
  void readCounts();
  void sendCounts();
  void writeCounts();
  void readSysMap();  
 
  void updateRadios(CMsg &msg);    
  void callCustomFunctions(CMsg &msg); 
};

CSatellite* getSatellite();
