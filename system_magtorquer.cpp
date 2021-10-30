#include "system_magtorquer.h"

#define MAGDELAY 50
#define MAGIMUINTERVAL 50

CMagTorquer::CMagTorquer():CSystemObject(){    
    Name("MT");
}

CMagTorquer::CMagTorquer(CMsg &msg) {   
   _cmsg = msg;   
   Name(msg.getSys());
}

void CMagTorquer::setup()  {
  pMAGX=(CMDrive *)getSystem("MAGX");
  pMAGY=(CMDrive *)getSystem("MAGY");
  pMAGZ=(CMDrive *)getSystem("MAGZ");
  pIMU= (CIMU *)getSystem("IMU");
  _INTERVAL = 20;
  _forever=true;

  _timeEnd=0;
  _timeStart=getTime();
  setState("PLAY");
  }


bool CMagTorquer::calcDiffs(){
  if (pIMU->runOnce()){       

     if((abs(pIMU->Mag.X)>200) || (abs(pIMU->Mag.Y)>200)  || (abs(pIMU->Mag.Z)>200)) return false;   //Bad data  continue
    
     float estx = pIMU->Mag.K_X();
     float esty = pIMU->Mag.K_Y();
     float estz = pIMU->Mag.K_Z();
  
     _difx=(estx-_lastx);
     _dify=(esty-_lasty);
     _difz=(estz-_lastz);
     
     char buf[80];
     
     snprintf(buf,70, "%.4f, %.4f, %.4f, %.1f",_difx,_dify,_difz);
     
     _lastx=estx;
     _lasty=esty;
     _lastz=estz;
     
     writeconsoleln(buf);
     //sendLora(buf);
     return true;
  }
}


void CMagTorquer::Detumble(){  
  if(_bMagOn){
    if(getTime()>_lastMag +MAGIMUINTERVAL){
      pMAGX->Stop();
      pMAGY->Stop();
      pMAGZ->Stop();
      _bMagOn=false;
      _lastMag=getTime();
    }
    return;
  }
  
  if(getTime()<_lastMag+MAGDELAY)
    return;
    
  if(calcDiffs()) {               
    if ((abs(_difx)<0.3)&&(abs(_dify)<0.3)&&(abs(_difz)<0.3)){
      Done();      
      return;
    }
     if (_difx>0.3) pMAGX->Forward();
     if (_dify>0.3) pMAGY->Forward();
     if (_difz>0.3) pMAGZ->Forward();

     if (_difx<-0.3) pMAGX->Backward();
     if (_dify<-0.3) pMAGY->Backward();
     if (_difz<-0.3) pMAGZ->Backward();
     
     _bMagOn=true;
     _lastMag=getTime();
    }   
  }


void CMagTorquer::loop(){ 
  _currentTime=getTime();
  
  Detumble();   
}  
