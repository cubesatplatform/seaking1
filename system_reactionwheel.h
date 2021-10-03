#pragma once
#include <map>
#include <systemobject.h>
#include "system_imu.h"
#include <fhmotor.h>
 
    
class CRW:public CSystemObject{
  private:    
     CIMU *_pIMU; //Open I2C ADR jumper - goes to address 0x4B

     float _speedX=0.0;
     float _speedY=0.0;
     float _speedZ=0.0;
    
  public:
    CRW();
    CRW(CMsg &msg);
    ~CRW(){}
    void setup();
    void initMode();
    void initManual();
    void initAuto();
    void loop();
    void modeAuto();
    void modeManual();
    void setSpeed();
    bool calcManual();
    bool calcAuto();
    bool calcAngles(){};  
    void deactivateGyro(CMsg &msg);
    bool activateGyro(CMsg &msg) ;
    bool activateGyro(char axis,float val) ;  
};
