#include "state_deployantenna.h"
#include "cubesat.h"


 void CDeployAntennaState::enter() { 
      CStateObj::enter();
      writeconsole("Enter Deploy Antenna"); 
      CSatellite *psat= getSatellite();
      psat->_burncount++;
      delay(100);
     
     }
