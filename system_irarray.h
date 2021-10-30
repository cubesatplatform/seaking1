#pragma once
#include <defs.h>

#include <systemobject.h>
#include <Adafruit_MLX90640.h>
#include "defs.h"



class CIRArray:public CSystemObject{
private:
  int imin,imax;
  TwoWire *pWire=&Wire;

  Adafruit_MLX90640 mlx;
  float frame[32*24]; // buffer for full frame of temperatures

  //paramsMLX90640 mlx90640;
  //float mlx90640To[768];
  char pixelTable[770];  //need it null terminated
  char _address=IRARRAY_ADDRESS_X1; 
  float fmin,fmax;
  long _interval=5000;
  char calcStart = 0x33; //Pin that goes high/low when calculations are complete
  //This makes the timing visible on the logic analyzer
  char cState='a';

public:
 CIRArray(CMsg &msg) {
  CIRArray();
  
  _cmsg=msg;

  //CID(msg.CID());
  
  _address = msg.getParameter("ADDRESS", _address);
  Name(msg.getParameter("NAME", Name()));
  char wireNum=msg.getParameter("WIRENUM", '0');
  if(wireNum='1') pWire=&Wire1;
//  if(wireNum='2') pWire=&Wire2;
  }
  
 CIRArray() {
    Name("IRARRAY");
    _forever =true;
        
    _INTERVAL = 5000;
    _transmitINTERVAL = 6000;    
    
  }

  void config(const char *name, char addr, char wireNum) {
    Name(name);
    if(wireNum=='1') pWire=&Wire1;
//  if(wireNum=='2') pWire=&Wire2;
    _address=addr;
    _forever =true;
            
  }

  bool isConnected();
  void setup();
  void loop();
  bool runOnce();
  std::string strData(int z);
  void Output();
  void callCustomFunctions(CMsg &msg);

};
