#include "system_reactionwheel.h"

//https://randomnerdtutorials.com/esp32-pwm-arduino-ide/
//https://circuits4you.com/2018/12/31/esp32-pwm-example/
//https://circuits4you.com/2017/12/21/esp8266-pwm-example/``
// the number of the LED pin
const int ledPin = 2;  // 16 corresponds to GPIO16



CRW::CRW():CSystemObject(){
    Name("RW");
    _Mode="MANUAL";
}

CRW::CRW(CMsg &msg) {   
   _cmsg = msg;   
   Name(msg.getSys());
   _Mode=msg.getMODE();
   
}




void CRW::setup()
  {

    _pIMU=(CIMU *)getSystem("IMU");
   
    if(_pIMU==NULL){         
      _pIMU=(CIMU *)getSystem("IMUI2C");
      if(_pIMU==NULL){
        writeconsoleln("ERROR   COULDNT START IMU.  Called from Reaction Wheel ...........................................");
        delay(2000);
        setState("ERROR");
        return;
      }
    }   

    _INTERVAL = 20;
    _forever=true;


    setState("PLAY");
  }

void CRW::initMode(){
  if (_Mode=="AUTO"){}  
  if (_Mode=="AUTO") initAuto();   
  if (_Mode=="MANUAL") initManual();    
}    

void CRW::initManual(){
   _currentTime=getTime();
   _cmsg.setParameter("XSPEED",(float)1.0);
   _cmsg.setParameter("XDURATION",(float)10000.0);

}

void CRW::initAuto(){
    _currentTime=getTime();
}


bool CRW::calcAuto(){
 
     return true;

}

bool CRW::calcManual(){
  
 
   
  return true;  
}


void CRW::setSpeed(){   
 

  CMsg m;
  m.Parameters["SYS"]="MOTORX";
  m.Parameters["ACT"]="UPDATE";
  m.Parameters["SPEED"]=_speedX;
  addMessageList(m);

  m.Parameters["SYS"]="MOTORY";
  m.Parameters["ACT"]="UPDATE";
  m.Parameters["SPEED"]=_speedY;
  addMessageList(m);


  m.Parameters["SYS"]="MOTORZ";
  m.Parameters["ACT"]="UPDATE";
  m.Parameters["SPEED"]=_speedZ;
  addMessageList(m);
}
  

void CRW::modeManual(){   
  calcManual();

  setSpeed();   
  if((_speedX==0.0)&&(_speedX==0.0)&&(_speedX==0.0))
    setState("COMPLETE");
}



void CRW::modeAuto(){   
  calcAuto();
  setSpeed();   

}
  


 
void CRW::loop(){ 
  _currentTime=getTime();
  bool flag=_pIMU->runOnce();

  if(flag==false) return;
  if (_Mode=="AUTO"){}  
  if (_Mode=="AUTO") modeAuto();   
  if (_Mode=="MANUAL") modeManual();   
}
