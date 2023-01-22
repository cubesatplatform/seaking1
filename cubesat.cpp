#include "cubesat.h"

CSatellite::CSatellite() {  }


void CSatellite::setup() {    //Anything not in a loop must be setup manually  or have setup done automatically when called    
  _state_adcs.name(_ADCS);
  _state_core.name(_CORE);  
  _state_deployantenna.name(_DEPLOY);
  _state_detumble.name(_DETUMBLE);
  _state_lowpower.name(_LOWPOWER);  
  _state_normal.name(_NORMAL);
  _state_payload.name(_PAYLOAD);
  
  _manager.name(_MANAGER);
  _messages.name(_MESSAGES);    
  _keyboard.name(_KEYBOARD);
  
  _IMUI2C.name(_IMUI);   
  _IMUSPI.name(_IMUS);
  
  _ir_X1.name(_IRX1);
  _ir_X2.name(_IRX2);
  _ir_Y1.name(_IRY1);
  _ir_Y2.name(_IRY2);
  _ir_Z1.name(_IRZ1);
  _ir_Z2.name(_IRZ2);

  _magneTorquers.name(_MAGNETORQUERS);
  _magX.name(_MAGX);
  _magY.name(_MAGY);
  _magZ.name(_MAGZ);

/*
  _gps.name(_GPS);
  
  _motorX.name(_MOTORX);
  _motorY.name(_MOTORY);
  _motorZ.name(_MOTORZ);
*/
  _phone.name(_PHONE);
 // _power.name(_POWER);
 
  _radio.name(_RADIO);
  //_radio2.name(_RADIO2);                                //Warning!!!  When one radio Radio2 is #defined as Radio as well

  //_reactionWheels.name(_RW);
  _scheduler.name(_SCHEDULER);

  _tempX1.name(_TEMPX1);
  _tempX2.name(_TEMPX2);
  _tempY1.name(_TEMPY1);
  _tempY2.name(_TEMPY2);
  _tempZ1.name(_TEMPZ1);
  _tempZ2.name(_TEMPZ2);
  _tempOBC.name(_TEMPOBC);  


///////////////////////////////////////////////////////////////////////    

  //state_normal.addSystem(&MotorX);  
  //state_core.addSystem(&ReactionWheels);    //RW needs to be in core because if you are running it you cant switch states and turn it off  
  
  _state_core.addSystem(&_messages);
  _state_core.addSystem(&_radio);      
  _state_core.addSystem(&_phone);      
  //_state_core.addSystem(&_scheduler);  
  
  _state_core.addSystem(&_keyboard);
  
  //_state_core.addSystem(&_power);    
  //_state_core.addSystem(&_radio2);
 _state_core.setForever();
  
  _radio.setTransmitter(true);
  _radio.setReceiver(true);
  _radio.setReceiver(false);
  _radio2.setTransmitter(false);

  
  addSystem(&_state_normal);

  //_state_normal.addSystem(&_state_lowpower);

  _state_normal.setMaxTime(MAXRUNTIME);
  _state_normal.onEnter[_PINOBCI2C]=true;
  _state_normal.onExit[_PINOBCI2C]=true;


  _state_lowpower.setMaxTime(MAXRUNTIME);
  _state_lowpower.onEnter[_PIN65V]=true;
  _state_lowpower.onEnter[_PINBURNWIRE]=true;
  _state_lowpower.onEnter[_PINOBCI2C]=true;
  _state_lowpower.onEnter[_PINPHONEPOWER]=true;  

  
  
 // _state_detumble.addSystem(&_MagneTorquers);
 // _state_detumble.addSystem(&_IMUI2C);
 // _state_detumble.addSystem(&_IMUSPI);
 // _state_detumble.addSystem(&_magX);
 // _state_detumble.addSystem(&_magY);
 // _state_detumble.addSystem(&_magZ);
      
//  _state_adcs.addSystem(&_ReactionWheels);
//  _state_adcs.addSystem(&_IMUI2C);
//  _state_adcs.addSystem(&_IMUSPI);
//  _state_adcs.addSystem(&_motorX);
//  _state_adcs.addSystem(&_motorY);
//  _state_adcs.addSystem(&_motorZ);
     
 // _state_payload.addSystem(&_phone);

///////////////////////////////////////////////////////////////////////
    

 // _state_deployantenna.setMaxTime(10000);
  _state_deployantenna.onEnter[_PINBURNWIRE]=true;
  _state_deployantenna.onExit[_PINBURNWIRE]=true;
  
 // _state_adcs.setMaxTime(2*TIMEORBIT);
  _state_adcs.onEnter[_PIN65V]=true;
  _state_adcs.onEnter[_PINADCSI2C]=true;
  _state_adcs.onExit[_PIN65V]=true;
  _state_adcs.onExit[_PINADCSI2C]=true;
  
 // _IMUSPI.remap();

 
  _tempOBC.config(TEMP_OBC,&Wire);
  _tempX1.config(TEMP_X1,&Wire);
  _tempX2.config(TEMP_X2,&Wire);
  _tempY1.config(TEMP_Y1,&Wire1);
  _tempY2.config(TEMP_Y2,&Wire1);
  _tempZ1.config(TEMP_Z1,&Wire2);
  _tempZ2.config(TEMP_Z2,&Wire2);

  _ir_X1.config(IRARRAY_ADDRESS_X1,&Wire);
  _ir_X2.config(IRARRAY_ADDRESS_X2,&Wire);
  _ir_Y1.config(IRARRAY_ADDRESS_Y1,&Wire1);
  _ir_Y2.config(IRARRAY_ADDRESS_Y2,&Wire1);
  _ir_Z1.config(IRARRAY_ADDRESS_Z1,&Wire2);
  _ir_Z2.config(IRARRAY_ADDRESS_Z2,&Wire2);


 /*
  _motorX.config(MOTOR_X_SPEED,MOTOR_X_FG,MOTOR_X_DIR);
  _motorY.config(MOTOR_Y_SPEED,MOTOR_Y_FG,MOTOR_Y_DIR);
  _motorZ.config(MOTOR_Z_SPEED,MOTOR_Z_FG,MOTOR_Z_DIR);
*/
  _magX.config(MAG_ADDRESS_X,&Wire2);  
  _magY.config(MAG_ADDRESS_Y,&Wire2);  
  _magZ.config(MAG_ADDRESS_Z,&Wire2);
    
  //_state_core.setup();  
  
    
  #if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)
    //mountFS();
  #endif  


  _IMUI2C.remap();

  _IMUI2C.config(IMUADDRESS1,&Wire);
  
  delay(100);
  
  readCounts();  
  
  _restartcount++;
 // writeCounts();  
 _scheduler.initSat();  //Commands that are autoscheduled  
 initPins();
  
}

void CSatellite::loop(){
  _state_core.loop();
  CStateObj::loop();
}

void CSatellite::changeState(CMsg &msg) {    //Changes states by adding clearing stateslist and adding core and the new state

  CMsg mm=getDataMap(_SATINFO);       
  addTransmitList(msg);  
  
  writeconsole("CHANGING STATE ......................Items: ");writeconsoleln((int)subsystems.size());
    
  std::string s=msg.get(_VALUE);

  if(mm.get(_STATE)==s){
    writeconsoleln("State the same.   Leaving.");
    return;
  }
  if(s.size()==0)
    return;

  CSystemObject *pstate=getSystem(s.c_str(),"CSatellite::newState(CMsg &msg)");
  
  if(pstate==NULL)
    return;

  unsigned int n=0;

  n=(unsigned int)pstate;
  writeconsole("New state ..cuz changing state ");
  writeconsole((long) n);
  writeconsoleln(pstate->name());
  
  for(auto x:subsystems){  //Tell subsystems you are leaving so they can do what they need
    n=(unsigned int)x;
    writeconsole("Tell Leaving cuz changing state ");
    writeconsole((long) n);
    writeconsoleln(x->name());
    if(x->name()!=_CORE)         x->exit();
  }

  subsystems.clear();   

          
  // pstate->stateMsg(msg);  //Passes parameters of what you want the state to do
  
  pstate->setMsg(msg);  //whatever stuff u want to send 
  pstate->enter();
  
//  addSystem(&_state_core);      /// Puts CORE BACK!!!! 
  addSystem(pstate);
  
  mm=getDataMap(_SATINFO);       mm.set(_STATE,s);      addDataMap(mm);      

  writeconsole("END CHANGING STATE ......................");writeconsoleln((int)subsystems.size());
}

void CSatellite::createState(CMsg &msg){  //Creates a completely new state Appends a state
  writeconsoleln("NNNNNNNNNNNNNNNNNNNNNN OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
  return;
  std::string s=msg.get(_VALUE);
  long lmax=msg.get(_MAXTIME,3*TIMEORBIT);
  if(s.size()>1){    
    CStateObj *pState=new CStateObj();
    pState->name(s);
    pState->setForever(false);
    pState->setMaxTime(lmax);
    addSystem(pState);


    CMsg m=getDataMap(_SATINFO); 
    std::string curst=m.get(_STATE);
    s+=";";
    s+=curst;
    m.set(_STATE,s);
    addDataMap(_SATINFO,m); 
  }  
}
