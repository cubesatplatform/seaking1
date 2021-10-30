#include "system_reactionwheel.h"

//https://randomnerdtutorials.com/esp32-pwm-arduino-ide/
//https://circuits4you.com/2018/12/31/esp32-pwm-example/
//https://circuits4you.com/2017/12/21/esp8266-pwm-example/``
// the number of the LED pin
//const int ledPin = 2;  // 16 corresponds to GPIO16


CRW::CRW():CSystemObject(){
    Name("RW");
   
}

CRW::CRW(CMsg &msg) {   
   _cmsg = msg;   

   Name(msg.getSys());

}


void CRW::setSpeed(CMsg &msg){
  CMotorController *pMotor=NULL;
  double ss;
           
  ss=msg.getParameter("MOTORX",(double)-99.9);      
  if(ss!=-99.9)
    pMotorX->setSpeed(ss);

  ss=msg.getParameter("MOTORY",(double)-99.9);      
  if(ss!=-99.9)
    pMotorY->setSpeed(ss);  

  ss=msg.getParameter("MOTORZ",(double)-99.9);      
  if(ss!=-99.9)
    pMotorZ->setSpeed(ss);
}

void CRW::setTmpSpeed(CMsg &msg){
  _tmpSpeed=msg;
  unsigned long ct=getTime();

  unsigned long ltimeX1=msg.getParameter("STARTTIMEX1",0);    
  unsigned long ltimeY1=msg.getParameter("STARTTIMEY1",0);    
  unsigned long ltimeZ1=msg.getParameter("STARTTIMEZ1",0);    

  unsigned long ldurationX1=msg.getParameter("DURATIONX1",1000);    
  unsigned long ldurationY1=msg.getParameter("DURATIONY1",1000);    
  unsigned long ldurationZ1=msg.getParameter("DURATIONZ1",1000);   


  _tmpSpeed.setParameter("MOTORX1",msg.getParameter("MOTORX1",0.0));
  _tmpSpeed.setParameter("MOTORY1",msg.getParameter("MOTORY1",0.0));
  _tmpSpeed.setParameter("MOTORZ1",msg.getParameter("MOTORZ1",0.0));
  _tmpSpeed.setParameter("STARTTIMEX1",ltimeX1+ct);    
  _tmpSpeed.setParameter("STARTTIMEY1",ltimeY1+ct);    
  _tmpSpeed.setParameter("STARTTIMEZ1",ltimeZ1+ct);    

  _tmpSpeed.setParameter("ENDTIMEX1",ltimeX1+ct+ldurationX1);    
  _tmpSpeed.setParameter("ENDTIMEY1",ltimeY1+ct+ldurationY1);    
  _tmpSpeed.setParameter("ENDTIMEZ1",ltimeZ1+ct+ldurationZ1);    

  _tmpSpeed.setParameter("STATE","ON");

  
}

void CRW::adjustSpeed(){
  CMotorController *pMotor=NULL;
  double ss;
  unsigned long ct=getTime();

  unsigned long tX=_tmpSpeed.getParameter("ENDTIMEX1",0);    
  unsigned long tY=_tmpSpeed.getParameter("ENDTIMEY1",0);    
  unsigned long tZ=_tmpSpeed.getParameter("ENDTIMEZ1",0);    

  if (!tX&&!tY&&!tZ) _tmpSpeed.Parameters.clear();

  if(ct>tX){
    pMotorX->setSpeed(_cmsg.getParameter("MOTORX",0)); 
    _tmpSpeed.setParameter("ENDTIMEX1",0);    
  }

  if(ct>tY){
    pMotorY->setSpeed(_cmsg.getParameter("MOTORY",0)); 
    _tmpSpeed.setParameter("ENDTIMEY1",0);        
  }

  
  if(ct>tZ){
    pMotorZ->setSpeed(_cmsg.getParameter("MOTORZ",0)); 
    _tmpSpeed.setParameter("ENDTIMEZ1",0);    
  }  

  tX=_tmpSpeed.getParameter("STARTTIMEX1",0);    
  tY=_tmpSpeed.getParameter("STARTTIMEY1",0);    
  tZ=_tmpSpeed.getParameter("STARTTIMEZ1",0);    

  if(tX&&(ct>tX)){
    pMotorX->setSpeed(_cmsg.getParameter("MOTORX",0)); 
    _tmpSpeed.setParameter("STARTTIMEX1",0);    
  }

  if(tY&&(ct>tY)){
    pMotorY->setSpeed(_cmsg.getParameter("MOTORY",0)); 
    _tmpSpeed.setParameter("STARTTIMEY1",0);        
  }

  
  if(tZ&&(ct>tZ)){
    pMotorZ->setSpeed(_cmsg.getParameter("MOTORZ",0)); 
    _tmpSpeed.setParameter("STARTTIMEZ1",0);    
  }

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

  pMotorX=(CMotorController *)getSystem("MOTORX");
  pMotorY=(CMotorController *)getSystem("MOTORY");
  pMotorZ=(CMotorController *)getSystem("MOTORZ");
  
  _INTERVAL = 20;
  _forever=true;  
  setSpeed(_cmsg);
  setState("PLAY");
}



  
void  CRW::callCustomFunctions(CMsg &msg){
  std::string act=msg.getACT();

  if(act=="RWSETSPEED") setSpeed(msg);
  if(act=="RWTMPSPEED") setTmpSpeed(msg);
    
  
  /*
  CMsg m;
  m.Parameters["MOTORX"]=1.0;
  m.Parameters["DURATION"]=50;
  m.Parameters["CALLBACK"]="MT";
  addMessageList(m);
  */
}

void CRW::loop(){ 
  if(_tmpSpeed.Parameters.size())
    adjustSpeed();
  pMotorX->loop();
  pMotorY->loop();
  pMotorZ->loop();
}
