#include "cubesat.h"

#include <map>
#include <list>
#include <bitset>




#if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)
  #include "mbed.h"
#else
  #define Wire2 Wire
  #include <axp20x.h>
  #include <boards.h>
#endif



////////////////////////  DONT WRITE TO SERIAL PORT BEFORE ITS DECLARED  -----   NO WRITING TO CONSOLE IN CONSTRUCTORS OF SYSTEMS THAT ARE BELOW ----------------------////////////////////////////////////////////////
////////////////////////REACTIONWHEEL #include <mbed.h>  IS CAUSE OF SPI ISSUES ---- Never include that!  ////////////////////////////////

#define WATCHDOGWAIT 32760  //This is the Max the Portenta can do


#define IAM "ADR1"
#define SAT IAM


CSatellite sat;

void setup() {   }

void mysetup() {    
  sat.name(IAM);
  sat.setIAM(sat.name());
  
  Serial.begin(1000000);
  long tt=getTime();
  while (!Serial){
    if(getTime()>tt+10000)
      break;
  }
  Wire.begin();                                             //NEED to turn I2C ON   Otherwise CRASH
  Wire1.begin();
  Wire2.begin();
   
  

  #if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)
  //Super IMPORTANT  Initialize SPIs so not floating!!!!
  
  //////////// WARNING   DOESNT WORK WITH PIN ALIASES   NO IDEA WHY
  digitalWrite(PC_13,HIGH);
  digitalWrite(PI_4,HIGH);
  digitalWrite(PJ_8,HIGH);
  //mbed_reset_reboot_count();
  //mbed::Watchdog::get_instance().start(WATCHDOGWAIT); 
  #else
  initBoard();   
  //  esp_task_wdt_init(WDT_TIMEOUT, true); // panic so ESP32 restarts
//  esp_task_wdt_add(NULL); //add current thread to WDT watch
//Serial.println(ESP.getFreeHeap());
  Wire.begin(21,22);
  #endif
  
  while (!Serial&&(getTime()<10000))  ;
  writeconsoleln("Starting...");
  
  delay(1000);
  
  
  Wire.setClock(400000); 
  Wire1.setClock(400000); 
  Wire2.setClock(400000); 
  delay(1000);  
  
  sat.setup();           
} 



//Check to make sure time isnt getting too big and overflows (~50days), reset

void loop() {      
  CMsg msg;

  delay(1000);
  mysetup(); 

  msg.set(_COMMENT,"This is Major Tom to Ground Control");   
  msg.setTIMESTAMP();  
  sat.addTransmitList(msg);

  while(1){   
    sat.loop();  
//    count++; 
    #if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)
//      if(count%WATCHDOG_LOOP_COUNT==0) mbed::Watchdog::get_instance().kick();   
    #endif 
        
  }      
}
