#include "cubesat.h"
#include "satwatchdog.h"

#include <map>
#include <list>
#include <bitset>


////////////////////////  DONT WRITE TO SERIAL PORT BEFORE ITS DECLARED  -----   NO WRITING TO CONSOLE IN CONSTRUCTORS OF SYSTEMS THAT ARE BELOW ----------------------////////////////////////////////////////////////
////////////////////////REACTIONWHEEL #include <mbed.h>  IS CAUSE OF SPI ISSUES ---- Never include that!  ////////////////////////////////

//Prefill the default states  Ex.  Detumble state should have detumble as a system.  DeployAntenna state should have deploy logic in it


CSatWatchdog satdog;
CSatellite sat;


CMessages* getMessages() { return &sat.MSG; }
CSystemObject *getSystem(const char *sys){ return sat.SysMap[sys]; }   //Due to polymorphism, will return whatever system you want
CSatellite* getSatellite() { return &sat; }


void setup() { // leave empty 
  #ifdef MYESP32
//  esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
//  esp_task_wdt_add(NULL); //add current thread to WDT watch
  #endif
  }



void mysetup() {  //init here
  Serial.begin(115200);
  satdog.setup();
  
  while (!Serial&&(getTime()<15000))  ;
  writeconsoleln("Starting...");
  delay(1000);
  Wire.begin();
  Wire.setClock(400000); //Increase I2C clock speed to 400kHz
  delay(1000);
  
  
  sat.setup();        
} 
 


//Check to make sure time isnt getting too big and overflows (~50days), reset

void loop() {  
  mysetup(); 
  long lastTime=0;
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
   while( sat.loop()){ 
   

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
      lastTimeA=getTime();
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
  }


  satdog.loop();    
    
}
