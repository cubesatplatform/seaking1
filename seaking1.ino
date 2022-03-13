#include "cubesat.h"
#include "satwatchdog.h"

#include <map>
#include <list>
#include <bitset>

#ifdef TTGO1
#include <axp20x.h>
#include "boards.h"
#endif


////////////////////////  DONT WRITE TO SERIAL PORT BEFORE ITS DECLARED  -----   NO WRITING TO CONSOLE IN CONSTRUCTORS OF SYSTEMS THAT ARE BELOW ----------------------////////////////////////////////////////////////
////////////////////////REACTIONWHEEL #include <mbed.h>  IS CAUSE OF SPI ISSUES ---- Never include that!  ////////////////////////////////

std::map<std::string,CSystemObject *> SysMap;
std::map<std::string, PinName> Pins;
std::map<std::string, PinName> pwmPins;
std::map<std::string, std::string> I2CMap;

CSatWatchdog satdog;
CSatellite sat;
#if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)
  TwoWire mWire2(I2C_SDA2,I2C_SCL2); 
  TwoWire *getWire2(){mWire2.begin();return &mWire2;};
#else
  #define mWire2 Wire;
#endif  

std::string CSystemObject::_sat="ADR1";
CMessages* getMessages() { return &sat.MSG; }
CSatellite* getSatellite() { return &sat; }


void transmitError(const char *tmp){
  writeconsole("Critical Error: ");  writeconsoleln(tmp);
  CMsg msg;
  msg.setACT("TRANSMITDATA");
  msg.Parameters["ERROR"]=tmp;    

  sat.MSG.TransmitList.push_back(msg); 
} 


void setup() { // leave empty 
  
  Serial.begin(115200);
  while (!Serial);
  Wire.begin();                                             //NEED to turn I2C ON   Otherwise CRASH
  Wire1.begin();
  mWire2.begin();
  
  #ifdef TTGO1
   initBoard();   
  #endif 
  #ifdef MYESP32
//  esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
//  esp_task_wdt_add(NULL); //add current thread to WDT watch
  #endif
  #if defined(PORTENTA_E22_900M30S) || defined(PORTENTA_E22_400M30S)  
  //Super IMPORTANT  Initialize SPIs so not floating!!!!
  digitalWrite(PC_13,HIGH);
  digitalWrite(PI_4,HIGH);
  digitalWrite(PJ_8,HIGH);
  mbed_reset_reboot_count();
  #endif
  }

void mysetup() {   
  satdog.setup();
  
 // while (!Serial&&(getTime()<15000))  ;
  writeconsoleln("Starting...");
  delay(1000);
  #if defined(TTGO) || defined(TTGO1)
   Wire.begin(21,22);
  #endif 
  
  Wire.setClock(400000); 
  delay(1000);  
  
  sat.setup();           
} 

void loop1() {
  Serial.println(".");  
}

//Check to make sure time isnt getting too big and overflows (~50days), reset
void loop() {  
  mysetup(); 
  unsigned count=0;
  CMsg msg;
  msg.setSYS("BASE");
  msg.setACT("Hello");   
  sat.addTransmitList(msg);

  while(1){   
    sat.loop();  
    count++; 
    if(count>4*WATCHDOG_LOOP_COUNT){  
      CMsg m;
      m.setSYS(sat.pstate->Name()); 
      #if defined(TTGO) || defined(TTGO1)
      m.setParameter("FREEHEAP",(long)ESP.getFreeHeap());
      #endif
      satdog.loop();    
      count=0;        
      writeconsoleln(m.serializeout());
    }  
  }      
}
