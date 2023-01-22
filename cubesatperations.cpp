#include "cubesat.h"


#if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)
void resetFunc(){
  NVIC_SystemReset();
}
#else
void(* resetFunc) (void) = 0; //declare reset function @ address 0
#endif


void CSatellite::callCustomFunctions(CMsg &msg)  {  //Used to be NewMsg
  
  std::string sys=msg.get(_SYS);
  std::string act=msg.get(_ACT);

  writeconsoleln("----------------------------------callCustomFunctions(CMsg &msg) ---");
  msg.writetoconsole();

  mapcustommsg(changeState)
  mapcustommsg(createState)


  mapcustom(readSysMap)
  mapcustom(resetFunc)
  mapcustom(sendCounts)   
  mapcustom(readCounts)   
  mapcustom(writeCounts)   
  

#if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)  
  mapcustommsg(updateRadios)
  /*
  mapcustom(mountFS)
  //mapcustom(formateFS)
   
  if(act=="DELETEFILE") {std::string path=msg.get(_PATH);  deleteFile(path.c_str()); }   
  if(act=="DELETEFILES") {std::string path=msg.get(_PATH);  deleteFiles(path.c_str()); }   
  if(act=="WRITEFILE") {std::string path=msg.get(_PATH);  writeFile(path.c_str(),(const unsigned char *)msg.serialize().c_str(),msg.serialize().size()); }   
  if(act=="APPENDFILE") {std::string path=msg.get(_PATH); std::string path1=msg.get(PATH1);   appendFile(path.c_str(),path1.c_str()); }   
  if(act=="READFILE") {std::string str,path=msg.get(_PATH); str=readFile(path.c_str()); CMsg m(str);  addTransmitList(m); }   
  if(act=="READFILEBINARY") {std::string str,path=msg.get(_PATH); CMsg m; str=readFileBinary(path.c_str(),&m.byteVector);   addTransmitList(m); }   
  if(act=="LISTDIR"){std::string str,path=msg.get(_PATH);CMsg m=listDir(path.c_str());    addTransmitList(m);}
  if(act=="FILESIZE") {std::string str,path=msg.get(_PATH); CMsg m=fileSize(path.c_str());   addTransmitList(m); }   
  */
 #endif
CSystemObject::callCustomFunctions(msg);
}


void CSatellite::updateRadios(CMsg &msg){  
  /*
    std::string transmitter=msg.get(TRANSMITTER);
    std::string sleeper=msg.get(SLEEP);
    writeconsoleln("updateRadios(CMsg &msg)");
    writeconsoleln(transmitter);

    if(transmitter.size()){
      if(transmitter==RADIO) {
          _radio.setTransmitter(true);
          _radio2.setTransmitter(false);
      }
      if(transmitter==RADIO2) {        
          _radio.setTransmitter(false);
          _radio2.setTransmitter(true);
      }    
    }

    if(sleeper.size()){
      if(sleeper==RADIO) {
          _radio.sleep(true);        
      }
      if(sleeper==RADIO2) {        
          _radio2.sleep(true);
      }    
    }
    */
}


void CSatellite::readSysMap(){
  writeconsoleln("SysMap List:");
  std::string str;
  std::string strName="SYSMAP";
  
  for(auto s:SysMap){
    writeconsoleln(s.first);    
    str+=s.first;
    if(str.size()>150){
      CMsg m;
      m.set(_LOG,_SYSTEMS);
      m.set(strName,str);    
      writeconsoleln(str);
      addTransmitList(m);      
      str="";      
    }
  }
  
  CMsg m;
  m.set(_LOG,_SYSTEMS);
  m.set(strName,str);    
  writeconsoleln(str);
  addTransmitList(m);
}



void CSatellite::readCounts() {
  CMsg msgCounts;
 // msgCounts.deserializeFile(_SATCOUNTS_FILE);
  addDataMap(_SATINFO,msgCounts);

  msgCounts.writetoconsole();
  addTransmitList(msgCounts);   
}


void CSatellite::sendCounts() {  
  CMsg msg=getDataMap(_SATINFO); 
  addTransmitList(msg);   
}


void CSatellite::writeCounts() {  
  CMsg msgCounts=getDataMap(_SATINFO); 
  
  std::string fn=msgCounts.serializeFile(SATCOUNTS_FILE);
  addTransmitList(msgCounts);   
}
