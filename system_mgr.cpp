
#include "system_mgr.h"
#include <messages.h>
#include "cubesat.h"

    
CSystemMgr::~CSystemMgr(){}  
  
bool CSystemMgr::init(){
   
   setState("PLAY");
  
}


void CSystemMgr::setup(){init();}



void CSystemMgr::loop(){
  chkRadio();
  chkCurrentState();
  chkAllStates();
  chkTemperature();
  chkBattery();
  chkCoreSystems();
  chkMessages();
  
  sendHealth();
  sendBeacon();
  }


void CSystemMgr::displayCMDs() {

  writeconsoleln();
  writeconsoleln("Commands: ");
  writeconsoleln("----------------------------------------------------------------");
  std::string tmpstr;
  int n;
  for (auto it : Pins) {
    tmpstr = it.first;
    writeconsole(tmpstr.c_str());
    writeconsole(":");
    n = it.second;
    writeconsole(n);
  }
  writeconsoleln("----------------------------------------------------------------");
  writeconsoleln("MAGX, MAGY, MAGZ");
  writeconsoleln("I2C0, I2C1, I2C2");
  writeconsoleln("IMU0, IMU1, IMU2, IMUSPI");
  writeconsoleln("HPH_15, LPH_15, WPH_15   -  High,  Low,  PWM");
}


void CSystemMgr::newState(const char *str){
    CMsg msg;
    msg.setSTATE(str);
    addMessageList(msg);
  }
  




#ifdef TTGO
void CSystemMgr::initPins() {

  Pins["36"] = 36;
  Pins["39"] = 39;
  Pins["34"] = 34;
  Pins["35"] = 35;
  Pins["32"] = 32;
  Pins["33"] = 33;
  Pins["25"] = 25;
  Pins["14"] = 14;
  Pins["13"] = 13;
  Pins["2"] = 2;
  Pins["1"] = 1;
  Pins["3"] = 3;
  Pins["23"] = 23;
  Pins["4"] = 4;
  Pins["0"] = 0;
  Pins["22"] = 22;
  Pins["21"] = 21;
  pwmPins={"36","39","34","35","32","33","25","14","13","2","1","3","23","4","0","22","21"};
}
#else

void CSystemMgr::initPins() {
  
  Pins["PA_0"]=PA_0;
  //Pins["PA_1"]=PA_1;
  Pins["PA_10"]=PA_10;
  Pins["PA_11"]=PA_11;
  Pins["PA_12"]=PA_12;
  Pins["PA_13"]=PA_13;
  Pins["PA_14"]=PA_14;
  Pins["PA_15"]=PA_15;
  Pins["PA_2"]=PA_2;
//  Pins["PA_3"]=PA_3;
  Pins["PA_4"]=PA_4;
//  Pins["PA_5"]=PA_5;
  Pins["PA_6"]=PA_6;
  //Pins["PA_7"]=PA_7;
  Pins["PA_8"]=PA_8;
  Pins["PA_9"]=PA_9;
//  Pins["PB_0"]=PB_0;
 // Pins["PB_1"]=PB_1;
//  Pins["PB_10"]=PB_10;
  //Pins["PB_11"]=PB_11;
  //Pins["PB_12"]=PB_12;
  //Pins["PB_13"]=PB_13;
  Pins["PB_14"]=PB_14;
  Pins["PB_15"]=PB_15;
  Pins["PB_2"]=PB_2;
  Pins["PB_3"]=PB_3;
  Pins["PB_4"]=PB_4;
  //Pins["PB_5"]=PB_5;
  Pins["PB_6"]=PB_6;
  Pins["PB_7"]=PB_7;
  Pins["PB_8"]=PB_8;
  Pins["PB_9"]=PB_9;
  //Pins["PC_0"]=PC_0;
  //Pins["PC_1"]=PC_1;
  Pins["PC_10"]=PC_10;
  Pins["PC_11"]=PC_11;
  Pins["PC_12"]=PC_12;
  Pins["PC_13"]=PC_13;
  Pins["PC_14"]=PC_14;
  Pins["PC_15"]=PC_15;
  Pins["PC_2"]=PC_2;
  Pins["PC_3"]=PC_3;
  //Pins["PC_4"]=PC_4;
  //Pins["PC_5"]=PC_5;
  Pins["PC_6"]=PC_6;
  Pins["PC_7"]=PC_7;
  Pins["PC_8"]=PC_8;
  Pins["PC_9"]=PC_9;
  Pins["PD_0"]=PD_0;
  Pins["PD_1"]=PD_1;
  Pins["PD_10"]=PD_10;
  Pins["PD_11"]=PD_11;
  Pins["PD_12"]=PD_12;
  Pins["PD_13"]=PD_13;
  Pins["PD_14"]=PD_14;
  Pins["PD_15"]=PD_15;
  Pins["PD_2"]=PD_2;
  Pins["PD_3"]=PD_3;
  Pins["PD_4"]=PD_4;
  Pins["PD_5"]=PD_5;
  Pins["PD_6"]=PD_6;
  Pins["PD_7"]=PD_7;
  Pins["PD_8"]=PD_8;
  Pins["PD_9"]=PD_9;
  Pins["PE_0"]=PE_0;
  Pins["PE_1"]=PE_1;
  Pins["PE_10"]=PE_10;
  Pins["PE_11"]=PE_11;
  Pins["PE_12"]=PE_12;
  Pins["PE_13"]=PE_13;
  Pins["PE_14"]=PE_14;
  Pins["PE_15"]=PE_15;
  Pins["PE_2"]=PE_2;
  Pins["PE_3"]=PE_3;
  Pins["PE_4"]=PE_4;
  Pins["PE_5"]=PE_5;
  Pins["PE_6"]=PE_6;
  Pins["PE_7"]=PE_7;
  Pins["PE_8"]=PE_8;
  Pins["PE_9"]=PE_9;
  Pins["PF_0"]=PF_0;
  Pins["PF_1"]=PF_1;
  Pins["PF_10"]=PF_10;
  Pins["PF_11"]=PF_11;
  Pins["PF_12"]=PF_12;
  Pins["PF_13"]=PF_13;
  Pins["PF_14"]=PF_14;
  Pins["PF_15"]=PF_15;
  Pins["PF_2"]=PF_2;
  Pins["PF_3"]=PF_3;
  Pins["PF_4"]=PF_4;
  Pins["PF_5"]=PF_5;
  Pins["PF_6"]=PF_6;
  Pins["PF_7"]=PF_7;
  Pins["PF_8"]=PF_8;
  Pins["PF_9"]=PF_9;
  Pins["PG_0"]=PG_0;
  Pins["PG_1"]=PG_1;
  Pins["PG_10"]=PG_10;
  //Pins["PG_11"]=PG_11;
  //Pins["PG_12"]=PG_12;
  //Pins["PG_13"]=PG_13;
  
  Pins["PG_14"]=PG_14;
  Pins["PG_15"]=PG_15;
  Pins["PG_2"]=PG_2;
  Pins["PG_3"]=PG_3;
  Pins["PG_4"]=PG_4;
  Pins["PG_5"]=PG_5;
  Pins["PG_6"]=PG_6;
  Pins["PG_7"]=PG_7;
  Pins["PG_8"]=PG_8;
  Pins["PG_9"]=PG_9;
  Pins["PH_0"]=PH_0;
//  Pins["PH_1"]=PH_1;  ??Can go High not Low
  Pins["PH_10"]=PH_10;
  Pins["PH_11"]=PH_11;
  Pins["PH_12"]=PH_12;
  Pins["PH_13"]=PH_13;
  Pins["PH_14"]=PH_14;
  Pins["PH_15"]=PH_15;
  Pins["PH_2"]=PH_2;
  Pins["PH_3"]=PH_3;
//  Pins["PH_4"]=PH_4;
  Pins["PH_5"]=PH_5;
  Pins["PH_6"]=PH_6;

  
  Pins["PH_7"]=PH_7;
  Pins["PH_8"]=PH_8;
  Pins["PH_9"]=PH_9;
  
  Pins["PI_0"]=PI_0;
  Pins["PI_1"]=PI_1;
//  Pins["PI_10"]=PI_10;
//  Pins["PI_11"]=PI_11;
  Pins["PI_12"]=PI_12;
  Pins["PI_13"]=PI_13;
  Pins["PI_14"]=PI_14;

  
  Pins["PI_15"]=PI_15;
  Pins["PI_2"]=PI_2;
  Pins["PI_3"]=PI_3;
  Pins["PI_4"]=PI_4;
  Pins["PI_5"]=PI_5;
  Pins["PI_6"]=PI_6;
  Pins["PI_7"]=PI_7;
  Pins["PI_8"]=PI_8;
  Pins["PI_9"]=PI_9;
  Pins["PJ_0"]=PJ_0;
  Pins["PJ_1"]=PJ_1;
  Pins["PJ_10"]=PJ_10;
  Pins["PJ_11"]=PJ_11;
  Pins["PJ_12"]=PJ_12;
  Pins["PJ_13"]=PJ_13;
  Pins["PJ_14"]=PJ_14;
  //Pins["PJ_15"]=PJ_15;
  Pins["PJ_2"]=PJ_2;
  Pins["PJ_3"]=PJ_3;
//  Pins["PJ_4"]=PJ_4;
  Pins["PJ_5"]=PJ_5;
  Pins["PJ_6"]=PJ_6;
  Pins["PJ_7"]=PJ_7;
  Pins["PJ_8"]=PJ_8;
  Pins["PJ_9"]=PJ_9;
  Pins["PK_0"]=PK_0;
  Pins["PK_1"]=PK_1;
  Pins["PK_2"]=PK_2;
  Pins["PK_3"]=PK_3;
  Pins["PK_4"]=PK_4;
  Pins["PK_5"]=PK_5;
  Pins["PK_6"]=PK_6;
  Pins["PK_7"]=PK_7;
  
  pwmPins={"PH_15","PK_1","PJ_11","PG_7","PC_7","PC_6","PA_8"};
}

#endif


void CSystemMgr::setupIMUI2C(TwoWire *wire){  
  BNO080 myIMU;

  myIMU.enableDebugging();

  writeconsoleln("IMU I2C");
  for(int count=0; count<5;count++){
    writeconsoleln("IMU Loop");
    if (myIMU.begin(IMUADDRESS1,*wire) ){  //IMUADDRESS1

    writeconsoleln("IMU Loop TRUE");
      wire->setClock(400000); //Increase I2C data rate to 400kHz
    
      myIMU.enableRotationVector(50); //Send data update every 50ms
    
      writeconsoleln("Rotation vector enabled");
      writeconsoleln("Output in form i, j, k, real, accuracy");    

      long ct=millis();
      while(millis()<(ct+20000)){
         if (myIMU.dataAvailable() == true) {
//            writeconsole((float)myIMU.getPitch() * 180.0 / PI); // Convert pitch to degrees
            writeconsole(",");
    //        writeconsole(float)myIMU.getRoll() * 180.0 / PI); // Convert roll to degrees
            writeconsole(",");
    //        writeconsoleln(float)myIMU.getYaw() * 180.0 / PI); // Convert yaw / heading to degrees          
         }

        
      }
     return;     
    }
    else{
      writeconsoleln("IMU Loop IF");
      writeconsoleln("BNO080 not detected at default I2C address. Check your jumpers and the hookup guide.");
      delay(500);
       
    }
  }  
   return;
}


void CSystemMgr::setupIMUSPI(){
#if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)  
  BNO080 myIMU;
for(int retries=0;retries<5;retries++){
    if(myIMU.beginSPI(IMU_OBC_NSS, IMU_OBC_WAKE, IMU_OBC_INT, IMU_OBC_RST) == false)
    {
      writeconsoleln("BNO080 over SPI not detected. Are you sure you have all 6 connections? F");
      
    }
    else{ 
     //  myIMU.enableRotationVector(50); //Send data update every 50ms
     //   myIMU.enableGyro(50); //Send data update every 50ms
     myIMU.enableGyroIntegratedRotationVector(50); //Send data update every 50ms
  
      
     writeconsoleln("IMU Ready");
     return;
    }
  }
#endif  
}

void CSystemMgr::pinsOn(){
  writeconsoleln("---------------------------------------------------------------------------------------------HIGH..........");
  for (auto x:Pins){
     writeconsoleln(x.first.c_str());     
     digitalWrite(x.second, HIGH);    
     delay(250);
  }
}

void CSystemMgr::pinsOff(){
  writeconsoleln("----------------------------------------------------------------------------------------LOW..........");
  for (auto x:Pins){
      writeconsoleln(x.first.c_str());
     
     digitalWrite(x.second, LOW);    
     delay(250);
  }  
}


void CSystemMgr::phone(){
  #if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)
 //  pinMode(PA_11, OUTPUT);

  
   digitalWrite(PA_11, HIGH);  //
 // Serial1.begin(PHONE_BAUD_RATE);
#else  
   Serial1.begin(PHONE_BAUD_RATE,SERIAL_8N1, PHONE_TX, PHONE_RX);
#endif  

  Serial1.write("Hello");
   sendSerial("INIT"); //to synchronise Arduino and app
}

void CSystemMgr::sendSerial(const char* cmd) {    //Send to Phone
  Serial1.print(1);
  Serial1.flush();
  Serial1.print(",");
  Serial1.flush();
  Serial1.println(cmd);
  Serial1.flush();
  delayMicroseconds(500); 


  Serial.print("Sending to phone => ");
  Serial.print(cmd);
}


void CSystemMgr::burn(){
  #if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)
  // pinMode(PI_10, OUTPUT);
   digitalWrite(PI_10, HIGH);  //   
   delay(10000);
   digitalWrite(PI_10, LOW);  //   
   #endif
}




void CSystemMgr::enableI2C(){
  #if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)
 // pinMode(PA_12, OUTPUT);
  digitalWrite(PA_12, HIGH);  //

 // pinMode(PH_15, OUTPUT);
  digitalWrite(PH_15, HIGH);  //
  #endif
}

void CSystemMgr::loopWire(TwoWire *wire) {
  byte error, address;
  int nDevices;
  writeconsole("Scanning...");

  nDevices = 0;
  for(byte address = 1; address < 127; address++ ) {
    writeconsole(".");
    wire->beginTransmission(address);
    error = wire->endTransmission();
    if (error == 0) {
      writeconsoleln();
      writeconsole("I2C device found at address 0x");
      if (address<16) {
        writeconsole("0");
      }
      writeconsoleln(address);  //HEX
      nDevices++;
    }
    else if (error==4) {
      writeconsole("Unknow error at address 0x");
      if (address<16) {
        writeconsole("0");
      }
      writeconsoleln(address);  //HEX
    }    
  }
  if (nDevices == 0) {
     writeconsoleln();
    writeconsoleln("No I2C devices found\n");
  }
  else {
    writeconsoleln("done\n");
  }
  writeconsoleln();
  delay(150);          
}


void CSystemMgr::SendCmd(std::string str) {
  PinName  n = Pins[str];
  char action = 'H';

  writeconsole(str.c_str());

  if ((str[0] == 'H') || (str[0] == 'L') || (str[0] == 'W')) {
    action = str[0];

    str.erase(0, 1);
    writeconsole(">");
  }

  writeconsole(str.c_str());
  writeconsole(" ");
  writeconsole(action);
  writeconsole(":");
  n = Pins[str];
  writeconsoleln(n);

  if (str == "RADIO") {
  CRadio radio;
  radio.setup();
  return;
  }

#if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)
if  (str == "MAG"){
  Adafruit_DRV8830 drv;
  #define DRV_I2C_ADDR 0x60
  
  TwoWire myWire2(PH_12,PH_11); 

    pinMode(PA_12, OUTPUT);
  digitalWrite(PA_12, HIGH);  //

  pinMode(PH_15, OUTPUT);
  digitalWrite(PH_15, HIGH);  //

    if (! drv.begin(0X60, &myWire2)) {
    writeconsoleln("Failed to find DRV8830");
    while (1);
  }
  writeconsoleln("Adafruit DRV8830 found!");


   writeconsoleln("Forward");
  drv.run(FORWARD);
  drv.setSpeed(255);
  delay(5000);

  writeconsoleln("Release");
  drv.run(RELEASE);
  delay(500);

  writeconsoleln("Backward");
  drv.run(BACKWARD);
  drv.setSpeed(255);
  delay(5000);

  drv.run(RELEASE);
  return;
}

  
  if ( (str == "MAGX")||(str == "MAGY")||(str == "MAGZ")) {
    enableI2C();
    writeconsole(str.c_str());

    #ifndef TTGO
    //pinMode(PA_12, OUTPUT);
    digitalWrite(PA_12, HIGH);  //

    //pinMode(PH_15, OUTPUT);
    digitalWrite(PH_15, HIGH);  //

    TwoWire mWire2(PH_12,PH_11); 
    mWire2.begin();

    CMDrive MAG;
  //return;  
    delay(10);
    char address=ADDRESS_MAGX;
    if(str == "MAGY") {address=ADDRESS_MAGY;}
    if(str == "MAGZ") {address=ADDRESS_MAGZ;}
    
    
    

    MAG.config(str.c_str(),address,&mWire2);
   MAG.Speed(1.0);
 
      delay(5000);
    MAG.Speed(-1.0);
      
      delay(5000);
    
     MAG.Speed(0.0);
    #endif
    return;
  }
#endif

  if (str == "?") {
    displayCMDs();
    return;
  }

  if (str == "MOTOR") {
  //  Motor();
    return;
  }

  if (str == "ON") {
    pinsOn();
    return;
  }

  if (str == "OFF") {
    pinsOff();
    return;
  }

  if (str == "PHONE") {
    phone();
    return;
  }

  if (str == "BURN") {
    burn();
    return;
  }



  if (str == "IMUSPI") {
    writeconsole("IMU SPI");
    
    delay(10);
    setupIMUSPI();
    return;
  }
  
  if (str == "IMU0") {
    writeconsole("IMU0");
    Wire.begin();
    delay(10);
    setupIMUI2C(&Wire);
    return;
  }
  
  if (str == "IMU1") {
    writeconsole("IMU1");
    Wire1.begin();
    delay(10);
    setupIMUI2C(&Wire1);
    return;
  }

#if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)  
  if (str == "IMU2") {
    writeconsole("IMU2");
    TwoWire mWire2(PH_12,PH_11); 
    mWire2.begin();
    
    delay(10);
    setupIMUI2C(&mWire2);
    return;
  }
  #endif


  if (str == "I2C0") {
    enableI2C();
    writeconsole("I2C0");
    Wire.begin();
    delay(10);
    loopWire(&Wire);
    return;
  }

  if (str == "I2C1") {
    enableI2C();
    writeconsole("I2C1");
    Wire1.begin();
    delay(10);
    loopWire(&Wire1);
    return;
  }

  if (str == "I2C2") {
    enableI2C();
    writeconsole("I2C2");

    #ifndef TTGO
    TwoWire mWire2(PH_12,PH_11); 
    mWire2.begin();
    delay(10);
    loopWire(&mWire2);
    #endif
    return;
  }

  if (action == 'H') {
    writeconsole("High");
 //   pinMode(n, OUTPUT);
    delay(10);
    digitalWrite(n, HIGH);
    return;
  }

  if (action == 'L') {
    writeconsole("Low");
 //   pinMode(n, OUTPUT);
    delay(10);
    digitalWrite(n, LOW);
    return;
  }

  if (action == 'W'){
    writeconsole("PWM");
    if (pwmPins.find(str) != pwmPins.end()) {
      writeconsole(" Found");
      #ifdef TTGO
        ledcSetup(_channel, freq, resolution);   // configure LED PWM functionalitites
        ledcAttachPin(n, _channel);  // attach the channel to the GPIO to be controlled
        delay(50);
        ledcWrite(_channel, (int) 130); 
    
      #else
        analogWriteResolution(12);   
        for (int count=0;count<4000;count+=100){
          analogWrite(n,count);
          writeconsole("PWM: ");
          writeconsole(count);
          delay(200);
        }
      #endif
    }
  
    return;    
  }

}


 void CSystemMgr::powerLevel(CMsg &msg){
    float bat=msg.getParameter("LEVEL",0.0);

    if(bat>60){
      CSatellite *psat= getSatellite();
      if(!psat->_burncount&&psat-> deployantenna.stateCount()<2){
          msg.setSTATE("DEPLOY");
          addMessageList(msg);
      }
      else  if(!psat->_detumblecount&psat->detumble.stateCount()<2){
          msg.setSTATE("DETUMBLE");
          addMessageList(msg);
      }
      else if(0){
        msg.setSTATE("PHONE");
        addMessageList(msg);        
      }
      else {
        msg.setSTATE("NORMAL");
        addMessageList(msg);        
      }
    }  
 }

 void CSystemMgr::callCustomFunctions(CMsg &msg){
 std::string act=msg.getACT(); 
 
  if(act=="CHKCLOCKS") chkClocks();
  if(act=="CHKRADIO") chkRadio();
  if(act=="CHKCURRENTSTATE") chkCurrentState();
  if(act=="CHKALLSTATES") chkAllStates();
  if(act=="CHKTEMPERATURE") chkTemperature();
  if(act=="CHKBATTERY") chkBattery();
  if(act=="POWERLEVEL") powerLevel(msg);
  if(act=="CHKROTATION") chkRotation();
  if(act=="CHKCORESYSTEMS") chkCoreSystems();
  if(act=="CHKMESSAGES") chkMessages();
//  if(act=="") stateLowPower();
//  if(act=="") stateReallyLowPower();
//  if(act=="") stateDetumble();
  
  if(act=="SENDHEALTH") sendHealth();
  if(act=="SENDBEACON") sendBeacon();
  
//  if(act=="") RESET(){};

  //if(act=="") loopWire(TwoWire *wire);
  if(act=="ENABLEI2C") enableI2C();
  //if(act=="") SendCmd(std::string str);
  //if(act=="") setSTATE(const char *str="LOWPOWER");
  
  if(act=="ENABLEBURN") burn();
  if(act=="ENABLEPHONE") phone();
  if(act=="PINSON") pinsOn();
  if(act=="PINSOFF") pinsOff();
  if(act=="SETUPIMUSPI") setupIMUSPI();
  //if(act=="") setupIMUI2C(TwoWire *wire);
  if(act=="DISPLAYCOMMANDS") displayCMDs();

}
