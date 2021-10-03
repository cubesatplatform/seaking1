#include "system_magtorquer.h"


CMagTorquer::CMagTorquer():CSystemObject(){    
    Name("MT");
}

CMagTorquer::CMagTorquer(CMsg &msg) {   
   _cmsg = msg;   
   Name(msg.getSys());
}

void CMagTorquer::initMode(){
  }    


void CMagTorquer::setup()  {
  
  _INTERVAL = 20;
  _forever=true;

    _timeEnd=0;
    _timeStart=getTime();
    setState("PLAY");
  }



void CMagTorquer::modeManual(){   
//  calcManual();
  CMsg m;
  m.Parameters["SYS"]="MAGX";
  m.Parameters["ACT"]="TURNON";
  m.Parameters["SPEED"]=1.0;
  m.Parameters["DURATION"]=50;
  m.Parameters["CALLBACK"]="MT";
  addMessageList(m);
  m.Parameters["SYS"]="MAGY";
  m.Parameters["ACT"]="TURNON";
  m.Parameters["SPEED"]=1.0;
  m.Parameters["DURATION"]=50;
  m.Parameters["CALLBACK"]="MT";
  addMessageList(m);
  m.Parameters["SYS"]="MAGZ";
  m.Parameters["ACT"]="TURNON";
  m.Parameters["SPEED"]=1.0;
  m.Parameters["DURATION"]=50;
  m.Parameters["CALLBACK"]="MT";
  addMessageList(m);

  //if((_speedX==0.0)&&(_speedX==0.0)&&(_speedX==0.0))     setState("COMPLETE");
}

void CMagTorquer::modeDetumble(){   
    CMsg m;
    m.Parameters["SYS"]="MAGX";
    m.Parameters["ACT"]="SPEED";
    m.Parameters["SPEED"]=1.0;
    m.Parameters["DURATION"]=50;
    addMessageList(m);
    m.Parameters["SYS"]="MAGY";
    m.Parameters["ACT"]="SPEED";
    m.Parameters["SPEED"]=1.0;
    m.Parameters["DURATION"]=50;
    addMessageList(m);
    m.Parameters["SYS"]="MAGZ";
    m.Parameters["ACT"]="SPEED";
    m.Parameters["SPEED"]=1.0;
    m.Parameters["DURATION"]=50;
    addMessageList(m);   
}


void CMagTorquer::loop(){ 
  _currentTime=getTime();
  if (_Mode==""){}  
  if (_Mode=="AUTO") modeDetumble();   
  if (_Mode=="MANUAL") modeManual();    
 
}  

  
