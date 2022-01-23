#pragma once
#include <defs.h>

#include <state_lowpower.h>
#include <state_detumble.h>
#include <state_adcs.h>
#include <state_normal.h>
#include <state_deployantenna.h>
#include <state_core.h>
#include <state_phone.h>

#include <system_imu.h>
#include "system_irarray.h"
#include "system_reactionwheel.h"
#include "system_magtorquer.h"
#include "system_temperature.h"
#include "radio.h"
#include "messages.h"
#include <mdrive.h>
#include <fhmotor.h>
#include "system_mgr.h"
#include "phone.h"
#include "ceps.h"
#include "system_example.h"
#include "system_pins.h"

#if !(defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7))
  #include "system_gps.h"
#endif  



#include "messages.h"

class CSatellite:public CSystemObject {
  public:
	std::list<CSystemObject*> coresystems;

	unsigned long lcount=0;
  CCoreState Core;
 
  CDetumbleState detumble;
	CLowPowerState lowpower;   //0
	CNormalState normal;        //1
	CDeployAntennaState deployantenna;   //2
	CADCSState adcs;   //3

  CPhoneState phone;

#if !(defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7))
   CGPS gps;
#endif  

  CExample Example;
  CSystemMgr Mgr;


  CEPS Power;
  CRadio Radio; 
  CIMU IMUI2C;   
  CIMU IMUSPI;
  
  CRW RW;
  CMagTorquer MT;

  //CRadio Radio2; 
  CPhone Phone;  

  
  CMDrive MagX;
  CMDrive MagY;
  CMDrive MagZ;

  CMotorController MotorX;
  CMotorController MotorY;
  CMotorController MotorZ;

  CSatPins SatPins;
  
  CTemperatureObject TempX1,TempX2,TempY1,TempY2,TempZ1,TempZ2;

  CIRArray IRX1,IRX2,IRY1,IRY2,IRZ1,IRZ2;
  
  CStateObj* pstate;
	//std::bitset<10> satflag;  //initialized to 0  enum some flags HEALTHCHECK,TEMP, etc    satflag[HEALTHCHECK]

	CMessages MSG;  
	CSatellite();

	void newState(CMsg &msg);
  void newMsg(CMsg &msg);
 
	void setup();  
	void loop();
	void stats();
	void MsgPump();
};

CSatellite* getSatellite();
TwoWire *getWire2();
