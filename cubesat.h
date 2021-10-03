#pragma once
#include <defs.h>

#include "state_adcs.h"
#include "state_lowpower.h"
#include "state_normal.h"
#include "state_deployantenna.h"
#include "state_core.h"
#include "state_phone.h"

#include "system_imu.h"
#include "system_irarray.h"
#include "system_imu.h"
#ifdef TTGO
  #include "system_gps.h"
#endif  
#include "system_reactionwheel.h"
#include "system_magtorquer.h"
#include "radio.h"
#include "messages.h"
#include <mdrive.h>
#include "system_mgr.h"
#include "phone.h"
#include "system_light.h"
#include "ceps.h"



#include "messages.h"

class CSatellite {
	std::list<CSystemObject*> coresystems;

	unsigned long lcount=0;
	CLowPowerState lowpower;   //0
	CNormalState normal;        //1
	CDeployAntennaState deployantenna;   //2
	CADCSState adcs;   //3
  CCoreState Core;
  CPhoneState phone;
  

public:

 // CEPS Power;
  CRadio Radio; 
  CIMU IMUI2C;   
//  CLight Light;
//  CPWMController PWM1;
//  CPWMController PWM2;
//  CMDrive MAGX;
//  CMDrive MAGY;
//  CMDrive MAGZ;
  CMotorController MotorX;
//  CMotorController MotorY;
//  CMotorController MotorZ;
  //CPWM PWMPin;
//  CSystemMgr Mgr;
  //CRadio Radio2; 
 // CIMU IMUSPI;
//  CPhone Phone;  
//  CIRArray IRX1;
//  CIRArray IRX2;
//  CIRArray IRY1;
//  CIRArray IRY2;
//  CIRArray IRZ1;
//  CIRArray IRZ2;
  //CThermometer TempX1;
  //CThermometer TempX2;
  //CThermometer TempY1;
  //CThermometer TempY2;
  //CThermometer TempZ1;
  //CThermometer TempZ2;
  //CThermometer TempOBC;
  //CRW RW;
  //CMagTorquer MT;
#ifdef TTGO
//   CGPS gps;
#endif


  std::map<std::string,CSystemObject *> SysMap;
  CStateObj* pstate;
	//std::bitset<10> satflag;  //initialized to 0  enum some flags HEALTHCHECK,TEMP, etc    satflag[HEALTHCHECK]

	CMessages MSG;  
	CSatellite();

	void newState(CMsg &msg);
  void newMsg(CMsg &msg);
  void addSystem(const char *str,CSystemObject* psys, CStateObj &state);
 
	void setup();  
	bool loop();
	void stats();
	void MsgPump();
};

CSatellite* getSatellite();
