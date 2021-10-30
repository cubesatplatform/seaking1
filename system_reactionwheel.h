#pragma once
#include <map>
#include <list>
#include <systemobject.h>
#include "system_imu.h"
#include <fhmotor.h>
 
    
class CRW:public CSystemObject{
  private:    
     CMsg _tmpSpeed;
     CIMU *_pIMU; //Open I2C ADR jumper - goes to address 0x4B

     CMotorController *pMotorX;
     CMotorController *pMotorY;
     CMotorController *pMotorZ;

  public:
    CRW();
    CRW(CMsg &msg);
    ~CRW(){}
    void setup();
    void loop();
    void setSpeed(CMsg &msg);
    void setTmpSpeed(CMsg &msg);
    void adjustSpeed();
    void callCustomFunctions(CMsg &msg);
};
