#pragma once
#include <defs.h>

#include "state_lowpower.h"
#include "state_detumble.h"
#include "state_adcs.h"
#include "state_normal.h"
#include "state_deployantenna.h"
#include "state_core.h"
#include "state_phone.h"

#include "system_imu.h"
#include "system_irarray.h"
#include "system_imu.h"
#include "system_reactionwheel.h"
#include "system_magtorquer.h"
#include "radio.h"
#include "messages.h"
#include <mdrive.h>
#include "system_mgr.h"
#include "phone.h"
#include "system_light.h"
#include "ceps.h"
#include <portentafs.h>

#ifdef TTGO
  #include "system_gps.h"
#endif  



#include "messages.h"

class CSatellite {
  public:
	std::list<CSystemObject*> coresystems;

	unsigned long lcount=0;
  CDetumbleState detumble;
	CLowPowerState lowpower;   //0
	CNormalState normal;        //1
	CDeployAntennaState deployantenna;   //2
	CADCSState adcs;   //3
  CCoreState Core;
  CPhoneState phone;

  


  int _burncount=0;
  int _detumblecount=0;

  CEPS Power;
  CRadio Radio; 
  CIMU IMUI2C;   

  CSystemMgr Mgr;
  CRW RW;
  CMagTorquer MT;
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
