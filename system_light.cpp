 #include "system_light.h"
 #include "arduino.h"

CLight::~CLight(){ 
  
}
 
 void CLight::setup(){  //Never use Pin 23
  Name("LIGHT");
  _forever=true;

  _INTERVAL=10;

     CMsg m;
    m.Parameters["SYS"]="IMU";
    //m.Parameters["ACT"]="SPEED"; 
    //m.Parameters["SPEED"]="1.0";   
    //m.Parameters["DURATION"]="50";  
    m.Parameters["CALLBACK"]="LIGHT";
   
    addMessageList(m);
  
 }


  
 void CLight::loop(){
float x=_cmsg.getParameter("GYRO_X",0L);
unsigned long msgTime=_cmsg.getParameter("GYRO_T",0L);
if (msgTime==0)
  return;


if (getTime()>msgTime+100)
  return;

  writeconsole("---Speed Dif: ");
  writeconsoleln(getTime()-msgTime);
  
  
  if(x>0.01){
    CMsg m;
      m.Parameters["SYS"]="PWM1";
      m.Parameters["ACT"]="SPEED"; 
      m.Parameters["SPEED"]="1.0";   
      m.Parameters["DURATION"]="50";  
      //m.Parameters["CALLBACK"]="LIGHT";
     
      addMessageList(m);
      _cmsg.Parameters["x"]="0.0"; 
    
  }

    if(x<-0.01){
    CMsg m;
      m.Parameters["SYS"]="PWM2";
      m.Parameters["ACT"]="SPEED"; 
      m.Parameters["SPEED"]="1.0";   
      m.Parameters["DURATION"]="50";  
      //m.Parameters["CALLBACK"]="LIGHT";
     
      addMessageList(m);
      _cmsg.Parameters["x"]="0.0"; 
    
  }
  _cmsg.Parameters["GYRO_T"]="0";  //Shows it is complete so we dont use it again
 }
