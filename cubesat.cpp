#include "cubesat.h"


bool CSatellite::loop() {
    MsgPump();
    Core.loop();   
   
    pstate->loop();     
    return true;
  }

CSatellite::CSatellite() {
	pstate = &normal;
	}


void CSatellite::newState(CMsg &msg) {
    //writeconsoleln("    ________________________________________________________________________________________________________________  New State");
    std::string s=msg.getSTATE();
    if(s.size()>1){
      CStateObj *tmpstate=pstate;
      if (s == "LOWPOWER")  tmpstate = &lowpower;
      if (s == "NORMAL")  tmpstate = &normal;
      if (s == "DEPLOY")  tmpstate = &deployantenna;
      if (s == "ADCS")  tmpstate = &adcs;
      if (s == "DETUMBLE")  tmpstate = &detumble;
      if (s == "PHONE")  tmpstate = &phone;


      if(tmpstate!=pstate){  //Don't reset if you are already in that state
        writeconsole(s);
        writeconsoleln("    _______________________  New State");
        pstate->exit();
        pstate=tmpstate;
        pstate->stateMsg(msg);  //Passes parameters of what you want the state to do
        pstate->enter();
      }
    }
  }

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void CSatellite::newMsg(CMsg &msg) {
  std::string sys=msg.getSYS();
  std::string act=msg.getACT();

  if(sys!="CORE") return;
  if(act=="STATE") newState(msg);
  if(act=="STATS") stats();
  if(act=="RESET") resetFunc();
  if(act=="TRANSMITDATA") MSG.movetoTransmitList(msg);
  if(act=="DATALISTCLEAR") MSG.DataList.clear();
  if(act=="MESSAGESLISTCLEAR") MSG.MessagesList.clear();
  if(act=="TRANSMITLISTCLEAR") MSG.TransmitList.clear();
  if(act=="TRANSMITTEDLISTCLEAR") MSG.TransmittedList.clear();
}


void CSatellite::stats(){
  CMsg m=pstate->stats();
  MSG.TransmitList.push_back(m);
  m=Core.stats();
  MSG.TransmitList.push_back(m);
  
}

void CSatellite::setup() {    //Anything not in a loop must be setup manually  or have setup done automatically when called
    #if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)    
    CFS fs;
//  fs.writeFile(100);
//  fs.deleteFile();
    _burncount=fs.readFile();
    Serial.println();
  #endif

    SysMap["IMU"]=&IMUI2C;
 //   SysMap["IRX1"]=&IRX1;     
 
    addSystem("RADIO",&Radio,Core);  
 // addSystem("RADIO2",&Radio2,Core);     
  addSystem("POWER",&Power,Core);
 // addSystem("PHONE",&Phone,normal);
    addSystem("Mgr",&Mgr,Core);

    addSystem("MT",&MT,detumble);
    addSystem("RW",&RW,adcs);



/*
  
    MotorX.config("RWX",RW_SIG_X,RW_FG_X,RW_DIR_X);
    MotorY.config("RWY",RW_SIG_Y,RW_FG_Y,RW_DIR_Y);
    MotorZ.config("RWZ",RW_SIG_Z,RW_FG_Z,RW_DIR_Z);
  
    IRX1.config("IRX1",IRARRAY_ADDRESS_X1,'0');
    IRX2.config("IRX2",IRARRAY_ADDRESS_X2,'0');
    IRY1.config("IRY1",IRARRAY_ADDRESS_Y1,'0');
    IRY2.config("IRY2",IRARRAY_ADDRESS_Y2,'0');
    IRZ1.config("IRZ1",IRARRAY_ADDRESS_Z1,'0');
    IRZ2.config("IRZ2",IRARRAY_ADDRESS_Z2,'0');
   
    MAGX.config("MAGX",ADDRESS_MAGX,'0');
    MAGY.config("MAGY",ADDRESS_MAGY,'0');
    MAGZ.config("MAGZ",ADDRESS_MAGZ,'0');   
*/
  
  //TempX1.config("TEMPX1",TEMP_X1,'0');
  //TempX2.config("TEMPX2",TEMP_X2,'0');
  //TempY1.config("TEMPY1",TEMP_Y1,'0');
  //TempY2.config("TEMPY2",TEMP_Y2,'0');
  //TempZ1.config("TEMPZ1",TEMP_Z1,'0');
  //TempZ2.config("TEMPZ2",TEMP_Z2,'0');
  //TempOBC.config("TEMPOBC",TEMP_OBC,'0');
  

   Core.setup();
}


void CSatellite::MsgPump() {
	//Gets messages receieved from radio, pushes to message list and then pumps them out

	MSG.moveReceived();
  for (auto  it:MSG.MessagesList) {
	
    CMsg msg = it;
    
    newMsg(msg);   //Satellite
    Core.newMsg(msg);   //Core
		pstate->newMsg(msg);   //Current State
	}

	MSG.MessagesList.clear();//Probable make sure messages have all been processed.  I think they will as only thing that can add messages should be the loop
}


 void CSatellite::addSystem(const char *str,CSystemObject* psys,  CStateObj &state){

      std::string sysname=str;
      state.subsystems.push_back(psys);    
   
 }
