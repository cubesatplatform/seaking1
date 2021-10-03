
#include "system_imu.h"

#ifdef PORTENTA
#include <pinDefinitions.h>

#define IMU_OBC_NSS PinNameToIndex(PB_4)
#define IMU_OBC_RST PinNameToIndex(PI_14)
#define IMU_OBC_INT PinNameToIndex(PI_15)
#define IMU_OBC_WAKE PinNameToIndex(PB_3)
#endif

void CIMU::loop(){runOnce();}
bool CIMU::runOnce(){
     if((_ostate!="READY")&&(_ostate!="PLAY") )setup();
    if((_ostate!="READY")&&(_ostate!="PLAY") ) return false;
    if (myIMU.dataAvailable() == true) {
      GetData();      
      return true;
      }
    else {
      if(getTime()>(_dataUpdatedOn+100*1000)){  //Check if nothing for 100s
        setState("NONE");  //Reset IMU
        writeconsoleln("==========================  IMU RESET NOT HEARD IN 100 SECS ==============================");
      }
    }
  return false;
}

void CIMU::GetData(){
    //Look for reports from the IMU    
  //  writeconsoleln(" --------------------------------------------------------------------------------- GET IMU DATA ---------------------------------------------------------------------------");

      _dataUpdatedOn=getTime();
      PRY.archiveData();
      Quat.archiveData();
      Lin.archiveData();
      Gyro.archiveData();
      Mag.archiveData();
      
      PRY.Pitch=(myIMU.getPitch()) * 180.0 / PI; // Convert pitch to degrees
      PRY.Roll=(myIMU.getRoll()) * 180.0 / PI; // Convert roll to degrees
      PRY.Yaw=(myIMU.getYaw()) * 180.0 / PI; // Convert yaw / heading to degrees

      Quat.I=myIMU.getQuatI();
       
      Quat.J = myIMU.getQuatJ();
      Quat.K = myIMU.getQuatK();
      Quat.R = myIMU.getQuatReal();
      Quat.Acc = myIMU.getQuatRadianAccuracy();

      Lin.X = myIMU.getLinAccelX();
      Lin.Y = myIMU.getLinAccelY();
      Lin.Z = myIMU.getLinAccelZ();
      Lin.Acc = myIMU.getLinAccelAccuracy();



  //  gyrox = myIMU.getGyroX();
  //  gyroy = myIMU.getGyroY();
  //  Gyro.z = myIMU.getGyroZ();
      Gyro.X = myIMU.getFastGyroX();
      Gyro.Y = myIMU.getFastGyroY();
      Gyro.Z = myIMU.getFastGyroZ();

      Mag.X = myIMU.getMagX();
      Mag.Y = myIMU.getMagY();
      Mag.Z = myIMU.getMagZ();
      Mag.Acc = myIMU.getMagAccuracy();

      Mag.changedOn=getTime();
      Quat.changedOn=getTime();
      Lin.changedOn=getTime();
      PRY.changedOn=getTime();
      Gyro.changedOn=getTime();

      CMsg mGyro,mLin,mMag,mPRY;

      if (Gyro.anythingNew()){
        mGyro=Gyro.makeMessage("GYRO");
       // respondCallBack(m);
      }

      /*
      if (Lin.anythingNew()){
        mLin=Lin.makeMessage("LIN");
       // respondCallBack(m);
      }

      if (Mag.anythingNew()){
        mMag=Mag.makeMessage("Mag");
       // respondCallBack(m);
      }

      
      if (PRY.anythingNew()){
        mPRY=PRY.makeMessage("PRY");
       // respondCallBack(m);
      }

      mGyro.appendParams(mLin.Parameters);   
      mGyro.appendParams(mMag.Parameters);
      mGyro.appendParams(mPRY.Parameters);
      */

      if(mGyro.Parameters.size())
        respondCallBack(mGyro);
      
}    

 void CIMU::Output(CMsg &msg){  
  CMsg mGyro;
  mGyro=Gyro.makeMessage("GYRO");
  addTransmitList(mGyro);

}

  
void CIMU::init(){
  Name("IMU"); 
  _INTERVAL = 5;
  _forever=true;
}


void CIMU::setup(){
  
 // setupSPI();
  setupI2C();
}

void CIMU::setupSPI(){
#ifdef PORTENTA
    Name("IMUSPI");
//   myIMU.enableDebugging(Serial); //Pipe debug messages to Serial port
   delay(1000);

   
for(int retries=0;retries<5;retries++){
    if(myIMU.beginSPI(IMU_OBC_NSS, IMU_OBC_WAKE, IMU_OBC_INT, IMU_OBC_RST) == false)
    {
      writeconsoleln("BNO080 over SPI not detected. Are you sure you have all 6 connections? Freezing...");
      retrycount++;     
      setState("ERROR");
     
    }
    else{ 
     //  myIMU.enableRotationVector(50); //Send data update every 50ms
     //   myIMU.enableGyro(50); //Send data update every 50ms
     myIMU.enableGyroIntegratedRotationVector(50); //Send data update every 50ms
  
  
     setState("READY");
     writeconsole("IMU Ready");
     return;
    }
  }
#endif  
}

void CIMU::setupI2C(){
  Name("IMU");
  delay(100);
  Wire.flush();

for(int retries=0;retries<5;retries++){
  
  if (myIMU.begin(IMUADDRESS1) == false) {   //IMUADDRESS2
     unsigned int counter=10000;
     while(Wire.available()&&counter) {  Wire.read();counter--;}   //Flushes wire.  Then try again    Wire.flush() should do the same thing
     delay(1000);         
     retrycount++;     
     setState("ERROR");
    writeconsoleln("IMU Error...............................");
    }
  else{  
    Wire.setClock(400000);
    //  myIMU.enableRotationVector(50); //Send data update every 50ms
    //  myIMU.enableGyro(50); //Send data update every 50ms
    myIMU.enableGyroIntegratedRotationVector(50); //Send data update every 50ms
    
    
    setState("READY");
    writeconsoleln("IMU Ready...............................");
    
   return ;
  }
}
}
