#include "cubesat.h"
#include <portentafs.h>

void CSatellite::loop() {   
    MsgPump();  
    Core.loop();   
    pstate->loop();     
  }

CSatellite::CSatellite() {
  Name("SAT");
	pstate = &normal;
	}


void CSatellite::newState(CMsg &msg) {    
    std::string s=msg.getACT();
    if(s.size()>1){
      CStateObj *tmpstate=pstate;
      if (s == "LOWPOWER")  tmpstate = &lowpower;
      if (s == "NORMAL")  tmpstate = &normal;
      if (s == "DEPLOY")  tmpstate = &deployantenna;
      if (s == "ADCS")  tmpstate = &adcs;
      if (s == "DETUMBLE")  tmpstate = &detumble;
      if (s == "PHONE")  tmpstate = &phone;


      if(tmpstate!=pstate){  //Don't reset if you are already in that state        
        pstate->exit();
        pstate=tmpstate;
        pstate->stateMsg(msg);  //Passes parameters of what you want the state to do
        pstate->enter();
      }
    }

  }





#if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)
void resetFunc(){
  NVIC_SystemReset();
}
#else
void(* resetFunc) (void) = 0; //declare reset function @ address 0
#endif

void CSatellite::newMsg(CMsg &msg) {
  std::string sys=msg.getSYS();
  std::string act=msg.getACT();

  if(sys=="SAT") {    
    
    if(act=="STATS") stats();
    if(act=="RESET") resetFunc();
    if(act=="COUNTS") readCounts();
    if(act=="TRANSMITDATA") MSG.movetoTransmitList(msg);
    if(act=="DATALISTCLEAR") MSG.DataList.clear();
    if(act=="MESSAGESLISTCLEAR") MSG.MessageList.clear();
    if(act=="TRANSMITLISTCLEAR") MSG.TransmitList.clear();
    if(act=="TRANSMITTEDLISTCLEAR") MSG.TransmittedList.clear();
    if(act=="SENDDATA") MSG.sendData(msg);
    if(act=="SUBSCRIBE") MSG.subscribe(msg.getDATA());
    if(act=="UNSUBSCRIBE") MSG.unsubscribe(msg.getDATA());
     
    if((act=="NORMAL") ||(act=="LOWPOWER") ||(act=="DEPLOY") ||(act=="DETUMBLE") ||(act=="ADCS")||(act=="PHONE")){
      newState(msg);
    }
  } 
    else{
    CSystemObject *psys=getSystem(sys.c_str(),"CSatellite::newMsg(CMsg &msg)");
    if(psys!=nullptr){    
       psys->newMsg(msg);       
      }
    return;  
  } 
}


void CSatellite::stats(){
  pstate->stats();  
  Core.stats();  
}

void CSatellite::setup() {    //Anything not in a loop must be setup manually  or have setup done automatically when called
  Core.addSystem(&Radio);
  Core.addSystem(&Mgr);  

  IMUI2C.Name("IMUI2C");   
  IMUSPI.Name("IMUSPI");
  IRX1.Name("IRX1");
  IRX2.Name("IRX2");
  IRY1.Name("IRY1");
  IRY2.Name("IRY2");
  IRZ1.Name("IRZ1");
  IRZ2.Name("IRZ2");
  
  MagX.Name("MAGX");
  MagY.Name("MAGY");
  MagZ.Name("MAGZ");
  
  MotorX.Name("MOTORX");
  MotorX.Name("MOTORY");
  MotorX.Name("MOTORZ");
  
  TempX1.Name("TEMPX1");
  TempX2.Name("TEMPX2");
  TempY1.Name("TEMPY1");
  TempY2.Name("TEMPY2");
  TempZ1.Name("TEMPZ1");
  TempZ2.Name("TEMPZ2");
  TempOBC.Name("TEMPOBC");
  TempADCS.Name("TEMPADCS");

  #if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)    

    
  IRX1.config(IRARRAY_ADDRESS_X1,&Wire);
  IRX2.config(IRARRAY_ADDRESS_X2,&Wire);
  IRY1.config(IRARRAY_ADDRESS_Y1,&Wire1);
  IRY2.config(IRARRAY_ADDRESS_Y2,&Wire1);
  IRZ1.config(IRARRAY_ADDRESS_Z1,getWire2());
  IRZ2.config(IRARRAY_ADDRESS_Z2,getWire2());

  TempOBC.config(TEMP_OBC,&Wire);
  TempADCS.config(TEMP_ADCS,&Wire);
  TempX1.config(TEMP_X1,&Wire);
  TempX2.config(TEMP_X2,&Wire);
  TempY1.config(TEMP_Y1,&Wire1);
  TempY2.config(TEMP_Y1,&Wire1);
  TempZ1.config(TEMP_Z1,getWire2());
  TempZ2.config(TEMP_Z2,getWire2());
    
  MagX.config(MAG_ADDRESS_X,getWire2());  
  MagY.config(MAG_ADDRESS_Y,getWire2());  
  MagZ.config(MAG_ADDRESS_Z,getWire2());
  #endif
 // normal.addSystem(&IRX1);
 /*
      normal.addSystem(&IR);
    normal.addSystem(&IRX1);
    normal.addSystem(&IRX2);
    normal.addSystem(&IRY1);
    normal.addSystem(&IRY2);
    normal.addSystem(&IRZ1);
    normal.addSystem(&IRZ2);


   normal.addSystem(&IRX1);
    normal.addSystem(&Example);    
      
 
 //   detumble.addSystem(&IMUI2C);   
 //   detumble.addSystem(&IMUSPI);   
      
  //  normal.addSystem(&Temperature);  
  //  normal.addSystem(&TempX1);     
  //  normal.addSystem(&TempX2);     
  //  normal.addSystem(&TempY1);     
  //  normal.addSystem(&TempY2);     
  //  normal.addSystem(&TempZ1);     
  //  normal.addSystem(&TempZ2);     
  
    detumble.addSystem(&MT);
    detumble.addSystem(&MagX);
    detumble.addSystem(&MagY);
    detumble.addSystem(&MagZ);
    
    adcs.addSystem(&RW);
 // adcs.addSystem(&IMUI2C);   
 // adcs.addSystem(&IMUSPI);
    adcs.addSystem(&MotorX);
    adcs.addSystem(&MotorY);
    adcs.addSystem(&MotorZ);
    phone.addSystem(&Phone);
 



// Core.addSystem(&Radio2);
// Core.addSystem(&Power);
   Core.setup();  
  
  CMsg msg;
  msg.setSYS("MGR");
  msg.setACT("CMD_GPS_OUTPUT");   
// Mgr.addMessageList(msg);

  msg.setSYS("MGR");
  msg.setACT("CMD_IRX1_OUTPUT");   
//  Mgr.addMessageList(msg);

  msg.setSYS("MGR");
  msg.setACT("SHOWCOMMANDS");   
// Mgr.addMessageList(msg);

  msg.setSYS("SYSTEMMGR");
  msg.setACT("I2C1");
  Mgr.addMessageList(msg);
  CMsg msg;
  msg.setSYS("EXAMPLE");
  msg.setACT("START");
  Mgr.addMessageList(msg);
*/


  readCounts();
  
}


void CSatellite::readCounts() {
  #if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)    
  if(1){
     CFS fs;    
     deployantenna._burncount=fs.readFile();    
  }
  if(1){
     CFS fs;
     fs.setFilename(DETUMBLE_FILE);
     detumble._detumblecount=fs.readFile();      
  }
  if(1){
     CFS fs;  
     fs.setFilename(RS_FILE);
     _restartcount=fs.readFile();     
     _restartcount++;
     fs.deleteFile(); 
     fs.writeFile(_restartcount);    
  }

  
  CMsg msg;
  msg.setTABLE("INFO");
  msg.setParameter("RESTARTS",_restartcount);
  msg.setParameter("BURNS",deployantenna._burncount);
  msg.setParameter("DETUMBLES",detumble._detumblecount);
  
  Mgr.addTransmitList(msg);   
  #endif
}





void CSatellite::MsgPump() {
	//Gets messages receieved from radio, pushes to message list and then pumps them out
  CMsg msg;
	MSG.moveReceived();
  int count=0;
  while(  MSG.MessageList.size()){
    count++;
    if(count>20)
      break;
    msg = MSG.MessageList.back();
    MSG.MessageList.pop_back();
    if(msg.Parameters.size()){
      
      newMsg(msg);   //Satellite
      Core.newMsg(msg);   //Core
      if(msg.getParameter("PROCESSED","")=="1"){
        writeconsole(msg.getParameter("PROCESSED",""));writeconsoleln("______________________  CSatellite::MsgPump Processed  _______________________");
        continue;
      }
  	  pstate->newMsg(msg);   //Current State      
    }
	}

	MSG.MessageList.clear();//Probable make sure messages have all been processed.  I think they will as only thing that can add messages should be the loop
}
