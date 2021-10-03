#include <defs.h>
#include "stateobj.h"
#include "system_datarequest.h"

#ifdef TTGO
#include "system_gps.h"
#endif

#include "system_reactionwheel.h"
#include "system_irarray.h"
#include "system_light.h"


void CStateObj::addSystem(CMsg &msg){
  writeconsole("Adding System: ");
  std::string sys = msg.getSYS();
  std::string act = msg.getACT();
  std::string CMDID = msg.getCMDID();
  std::string ID = msg.getID();
  CSystemObject* psys=nullptr;
  psys=FindName(sys);
  if(psys!=nullptr){
     writeconsole("Error: Object ALREADY EXISTS    Turning existong one ON()");
     psys->on();
     return;
  }

  writeconsoleln(sys);
  writeconsoleln("");
  if(subsystems.size()>100) {
      writeconsole("Error: Too Many Objects    Not creating new one.");
      return; //Prevents from too many things running and blowing up system memory
    }
  

  #ifdef TTGO
  if (sys == "GPS") psys = new CGPS(msg);
  #endif

  if (sys == "IMU") psys = new CIMU(msg);
  if (sys == "RW") psys = new CRW(msg);
  if (sys == "LIGHT") psys = new CLight(msg);
  if (sys == "DATAREQUEST") psys = new CDataRequest(msg);
  

    if (sys == "RGB") {
      msg.Parameters["NAME"]="LIGHTRED";
      psys = new CLight(msg);
      if (psys!=NULL) subsystems.push_back(psys); 

       msg.Parameters["NAME"]="LIGHTGREEN";
      psys = new CLight(msg);
      if (psys!=NULL) subsystems.push_back(psys);

       msg.Parameters["NAME"]="LIGHTBLUE";
      psys = new CLight(msg);
      if (psys!=NULL) subsystems.push_back(psys);
    }

  if (psys!=NULL) subsystems.push_back(psys); 
}
