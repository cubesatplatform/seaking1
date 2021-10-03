#pragma once
#include <map>
#include <defs.h>
#include <systemobject.h>
#include "system_imu.h"
#include <mdrive.h>
 
    
class CMagTorquer:public CSystemObject{
  private:
    long _timeStart=0;
    long _timeEnd=0;
    long _timeLast=0;
    unsigned long _prevTime=0;
    
  public:
    CMagTorquer();
    CMagTorquer(CMsg &msg);
    ~CMagTorquer(){}

    void setup();
    void initMode();
      
    void loop();
  
    void modeDetumble();
    void modeManual();

    bool activateMag(CMsg &msg) ;
    bool activateMag(char axis,float val) ;
    
};
