#include "cubesat.h"
#include "satwatchdog.h"

#include <map>
#include <list>
#include <bitset>


////////////////////////  DONT WRITE TO SERIAL PORT BEFORE ITS DECLARED  -----   NO WRITING TO CONSOLE IN CONSTRUCTORS OF SYSTEMS THAT ARE BELOW ----------------------////////////////////////////////////////////////
////////////////////////REACTIONWHEEL #include <mbed.h>  IS CAUSE OF SPI ISSUES ---- Never include that!  ////////////////////////////////

std::map<std::string,CSystemObject *> SysMap;

CSatWatchdog satdog;
CSatellite sat;
#if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)
  TwoWire mWire2(I2C_SDA2,I2C_SCL2); 
#else
  #define mWire2 Wire
#endif  

std::string CSystemObject::_sat="ADR1";
CMessages* getMessages() { return &sat.MSG; }
CSatellite* getSatellite() { return &sat; }
TwoWire *getWire2(){return &mWire2;};

void transmitError(const char *tmp){
  writeconsole("Critical Error: ");  writeconsoleln(tmp);
  CMsg msg;
  msg.setACT("TRANSMITDATA");
  msg.Parameters["ERROR"]=tmp;    
  sat.MSG.newMessage(msg);  
}


void setup() { // leave empty 
  Serial.begin(115200);
  while (!Serial);
  #ifdef MYESP32
//  esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
//  esp_task_wdt_add(NULL); //add current thread to WDT watch
  #endif
  }

void mysetup() {   
  satdog.setup();
  
 // while (!Serial&&(getTime()<15000))  ;
  writeconsoleln("Starting...");
  delay(1000);
  Wire.begin();
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
  while(1 ){ 
    sat.loop();
    count++; 
    if(count>WATCHDOG_LOOP_COUNT){   
      writeconsoleln("");
      writeconsole("                            WatchDog Loop!!!           State:");
      writeconsoleln(sat.pstate->Name());
      satdog.loop();    
      count=0;
        /*
        CMsg msg;    
           msg.setSTATE("DETUMBLE");
          sat.Radio.addMessageList(msg);
        
        if (rand()%4==0){       
          msg.setSTATE("ADCS");
          sat.Radio.addMessageList(msg);  
        }
        if (rand()%4==1){       
          msg.setSTATE("DETUMBLE");
          sat.Radio.addMessageList(msg);  
        }
        if (rand()%4==2){       
          msg.setSTATE("LOWPOWER");
          sat.Radio.addMessageList(msg);  
        }
        */
        
    }  
  }      
}

/*
 * 
 *   
 *     long lastTime=0;
    long lastTimeA=0;

     long lastTimeB=0;
  bool flag=true;

  std::queue<std::string> Vlist;


  Vlist.push("CINIT");
  Vlist.push("CTIME");
  Vlist.push("CGPS");
  Vlist.push("CPHOTO(F,90%,100,100,AUTO)");
  Vlist.push("CPHOTO(F,50%,100,100,AUTO)");
  
  Vlist.push("CPHOTO(F,10%,100,100,AUTO)");
  Vlist.push("CSTREAM(273.png,0)");
  Vlist.push("CSTREAM(273.png,1)");
  Vlist.push("CSTREAM(273.png,2)");
  Vlist.push("CSTREAM(273.png,3)");
  Vlist.push("CSTREAM(273.png,4)");
  Vlist.push("CSTREAM(273.png,5)");
  
  int nspeed=8;
  std::string str;
  writeOut();  
     if(getTime()>lastTime+3000){
      writeconsole(".");
      
      lastTime=getTime();
     }  
        
    if(getTime()>lastTimeB+2000){
      str="";
      if(Vlist.size()){
        str=Vlist.front();
        Vlist.pop();
      }
    
      if(str.size()>1){       
        lastTimeB=getTime();
        CMsg msg;
        msg.setSYS("PHONE");
        msg.setACT(str);
        sat.MSG.newMessage(msg);
      }
    }
 

    if(getTime()>lastTimeA+3){
      //writeconsole("...............Message Motor.....................");
      CMsg msg;
      lastTimeA=getTime();W
      msg.setSYS("MOTOR");
      msg.setACT("SPEED");
      nspeed*=-1;
      msg.setParameter("SPEED",(float)(nspeed/100.0));
      
    
      msg.Parameters["DURATION"]="1000";
      //       msg.setACT("TRANSMITDATA");
      //       msg.Parameters["FILE"]="273.png";
      //       msg.Parameters["BLK"]="2";
      sat.MSG.newMessage(msg);
    }
 */
