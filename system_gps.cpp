
#include <defs.h>

#ifdef TTGO

#include "system_gps.h"   
#include "systemobject.h"
#include <string>
#include <TinyGPS++.h>
#include <axp20x.h>

#include <consoleio.h>

HardwareSerial GPSL(1);


CGPS::CGPS()  {  
   init();
  }

CGPS::CGPS(CMsg &msg) {  
  
  _cmsg = msg;
  _cmsg.deserialize();
  init();
  Name(msg.getSYS());
  }


void CGPS::init()
{
   Name("GPS");
    
    writeconsole("GPS created");  
   // INTERVAL = atol(_cmsg.getParameter("INTERVAL").c_str());
    _INTERVAL = _cmsg.getParameter("INTERVAL",1000);
    _transmitINTERVAL =1000;
    _forever =true;
  
}

void CGPS::setup()
{
  //Serial.begin(115200);
  Wire.begin(TTGO_I2C_SDA, TTGO_I2C_SCL);
  if (!axp.begin(Wire, AXP192_SLAVE_ADDRESS)) {
    writeconsole("AXP192 Begin PASS");
  } else {
    writeconsole("AXP192 Begin FAIL");
  }
  axp.setPowerOutPut(AXP192_LDO2, AXP202_ON);
  axp.setPowerOutPut(AXP192_LDO3, AXP202_ON);
  axp.setPowerOutPut(AXP192_DCDC2, AXP202_ON);
  axp.setPowerOutPut(AXP192_EXTEN, AXP202_ON);
  axp.setPowerOutPut(AXP192_DCDC1, AXP202_ON);
  GPSL.begin(9600, SERIAL_8N1, 34, 12);   //17-TX 18-RX
  setState("READY");
}

void CGPS::loop()
{
  bool flag=false;
  unsigned int counter=10000;
   while (GPSL.available()&&counter){
      gpsl.encode(GPSL.read());
      flag=true;
      counter--;
   }

   if(flag){
    latitude=gpsl.location.lat();
    longitude=gpsl.location.lng();
    altitude=gpsl.altitude.feet();
    SIV=gpsl.satellites.value();
   // Yr=gpsl.time.year();
    //Mon=gpsl.time.month();
    //Day=gpsl.time.day();
    Hr=gpsl.time.hour();
    Min=gpsl.time.minute();
    Sec=gpsl.time.second();
    //Speed=gpsl.time.kmph()

    Output();
   }
 
}



CMsg CGPS::fillData(){  //Easier to send as long   convert to decimal when receive
  
   CMsg m;
   m.setParameter("table","gps");
   m.setParameter("lat",latitude);
   m.setParameter("lon",longitude);
   m.setParameter("alt",altitude);
   m.setParameter("siv",(long)SIV);
   m.setParameter("hr",(long) Hr);
   m.setParameter("min",(long) Min);
   m.setParameter("sec",(long) Sec);
   
  return m;
 }

 void CGPS::Output(){  
  CMsg m=fillData();
  addTransmitList(m,true);

}


#endif
