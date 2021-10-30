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
  
/*
  #ifdef TTGO
  if (sys == "GPS") psys = new CGPS(msg);
  #endif

  if (sys == "IMU") psys = new CIMU(msg);
  if (sys == "MT") psys =  &MT;
  if (sys == "MAGX") psys =  &MAGX;
  if (sys == "MAGY") psys =  &MAGY;
  if (sys == "MAGZ") psys =  &MAGZ;
  if (sys == "LIGHT") psys = new CLight(msg);
  if (sys == "DATAREQUEST") psys = new CDataRequest(msg);
*/
  psys=getSystem(sys.c_str());

  if (psys!=NULL) subsystems.push_back(psys); 
}
