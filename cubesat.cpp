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
    std::string s=msg.getParameter("STATE");
    if(s.size()>1){
      writeconsole(s);
      writeconsoleln("    _______________________  New State");
      pstate->exit();
      if (s == "LOWPOWER")  pstate = &lowpower;
      if (s == "NORMAL")  pstate = &normal;
      if (s == "DEPLOY")  pstate = &deployantenna;
      if (s == "ADCS")  pstate = &adcs;
      if (s == "PHONE")  pstate = &phone;
      pstate->stateMsg(msg);  //Passes parameters of what you want the state to do
      pstate->enter();
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

    SysMap["IMU"]=&IMUI2C;
 //   SysMap["IRX1"]=&IRX1;
 //   SysMap["LIGHT"]=&Light;
    
 //   SysMap["MAGX"]=&MAGX;
 //   SysMap["MAGY"]=&MAGY;
 //   SysMap["MAGZ"]=&MAGZ;

//    SysMap["MOTOR"]=(CSystemObject *)&MotorX;
 //   SysMap["MOTORY"]=&MotorY;
 //   SysMap["MOTORZ"]=&MotorZ;
    
   // addSystem("POWER",&Power,normal);
   // addSystem("PWM1",&PWM1,normal);     
   // addSystem("PWM2",&PWM2,normal);    
   
 //   addSystem("IMU",&IMUI2C,normal);    
   // addSystem("MOTOR",&MotorX,Core); 
 //   addSystem("LIGHT",&Light,normal);     
    addSystem("RADIO",&Radio,Core); 
      addSystem("RADIO",&Radio,normal); 
//  addSystem("RADIO2",&Radio2,Core);     
 // addSystem("PHONE",&Phone,normal);

//  addSystem("Mgr",&Mgr,Core);
//  addSystem("RW",&RW,Core);
//  addSystem("PWM",&PWMPin,Core);
//  addSystem("MT",&MT,adcs);


// MotorX.config("MOTOR",14,13,2);
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

   
    MAGX.config("MAGX",MAG_ADDRESS_X,'0');
    MAGY.config("MAGY",MAG_ADDRESS_Y,'0');
    MAGZ.config("MAGZ",MAG_ADDRESS_Z,'0');
    
*/
 //   PWM1.config("PWM1",13);
 //   PWM2.config("PWM2",4);
  
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
	//for (std::list<CMsg>::iterator it = MSG.MessagesList.begin(); it != MSG.MessagesList.end(); ++it) {
 //for (auto it = MSG.MessagesList.begin(); it != MSG.MessagesList.end(); ++it) {
 // CMsg msg = *it;
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
