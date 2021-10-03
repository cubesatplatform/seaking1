 #include "state_core.h"
#include "cubesat.h"


void CCoreState::setup(){  //Initialize all systems in SysMap
  for (auto s: getSatellite()->SysMap){
    s.second->setup();
    }  
}


 
