#include "phone.h"



/*
void CPhone::newCMD(CMsg &msg){
   writeconsoleln("..................................... Phone Adding Command Queue .....................................");
  commandQueue.push(msg);
}
*/

void  CPhone::callCustomFunctions(CMsg &msg){
  std::string act=msg.getACT();
  
  writeconsoleln(act);
  
  if(act.size()>1)  commandQueue.push(msg);
 
}


CPhone::CPhone(CMsg &msg){_cmsg=msg;init();}
CPhone::CPhone(){init();}


void CPhone::init(){
  Name("PHONE");
  _INTERVAL=20;
}
void CPhone::on(){
  writeconsoleln("..................................... SwitchtoOn -  Add Power Logic Here .....................................");
  setup(); 
  }

  
void CPhone::off(){
  //writeconsoleln("..................................... SwitchtoOff -  Add Power Logic Here .....................................");
  }


void CPhone::setup() {   
 // Serial1.begin(115200);
 // Serial1.setTimeout(TIMEOUT);

 writeconsoleln("..................................... Setup .....................................");

#if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)
  Serial1.begin(PHONE_BAUD_RATE);
#else  
  //Serial1.begin(PHONE_BAUD_RATE, SERIAL_8N1, PHONE_TX, PHONE_RX);
 // Serial1.begin(115200,SERIAL_8N1,13,14); 
  //Serial1.begin(115200,SERIAL_8N1,35,15); 
   Serial1.begin(PHONE_BAUD_RATE,SERIAL_8N1, PHONE_TX, PHONE_RX);
//    Serial1.begin(115200, SERIAL_8N1, 23,4);
#endif  
  sendSerial("INIT"); //to synchronise Arduino and app
  //setState("READY");
  setState("PLAY");
}


void CPhone::ready(){
  writeconsoleln("..................................... StartPlay .....................................");
  ReceivedPacket();  //Should hit onInit whch should set state to PLAY
}


bool CPhone::waitForBytes(int count) {   //Waits for data from serial port up to TIMEOUT secs   If it got the number of bytes, return true.   
  long start = getTime();
  while (Serial1.available() < count) {    //Get the number of bytes (characters) available for reading from the serial port. This is data that’s already arrived and stored in the serial receive buffer
    if (getTime() - start > TIMEOUT) {
      return false;
    }
  }
  return true;
}

bool CPhone::readUntil(char terminator, unsigned char* buffer) {    //Read from Phone
  for (int i = 0; i < BUFFER_LENGTH; i++) {
    bool ok = waitForBytes(1);
    if (!ok) return false;

    unsigned char b = Serial1.read();
    if (b == terminator) {
      buffer[i] = 0;
      return true;
    }
    else {
      if (i == BUFFER_LENGTH - 1) {
        return false;
      }
      else {
        buffer[i] = b;
      }
    }
  }
  return false;
}

void CPhone::sendSerial(const char* cmd) {    //Send to Phone
  Serial1.print(id);
  Serial1.flush();
  Serial1.print(",");
  Serial1.flush();
  Serial1.println(cmd);
  Serial1.flush();
  delayMicroseconds(500); 
  id++;

   writeconsoleln();
  writeconsole("Sending to phone => ");
  writeconsoleln(cmd);
}
    

 /*   

void push_stream(long id, byte* fileName, int block, int len, bool hasMore, byte* data) {
  message m;
  m.data[0] = id >> 8;                           //writing the parameters passed to the message structure
  m.data[1] = id;                                
  m.data[2] = 'S';
  m.data[3] = block >> 8;
  m.data[4] = block;
  m.data[5] = len;
  m.data[6] = hasMore;
  strcpy(m.data+7, (char*) fileName);
  int fnLen = strlen((char*) fileName);
  m.data[7 + fnLen] = 0;
  memcpy(m.data + fnLen + 8, data, len);
  
  m.length = len + fnLen + 8;
  
  if (queue.size() < 400) {
  //  queue.push(m);
  }
  else {
    writeconsoleln("Queue full!!!");
  }
}
*/



   
void CPhone::push_stream(long id, unsigned char* fileName, int block, int len, bool hasMore, unsigned char* data) {  //Gets Filename and offset sent to comms,  id is id of the phone
 char type = 'S';
std::string str;
//MAYBE USE CID AS ID
//X as first character denotes stream
//Capital B means no more
//std::string str = std::string("fileid:")+std::to_string(id)+std::string("~filename:")+std::string((char *)fileName)+std::string("~len:")+ std::to_string(int(len))+std::string("~more:")+ std::to_string(int(hasMore));
//if(hasMore)  str= std::string("cid:")+std::to_string(id)+std::string("~b:")+std::to_string(block);
//else str = std::string("X")+CID()+std::string("B")+std::to_string(block);
if(hasMore)  str= std::string("X")+CID()+std::string("b")+tostring(block);                    
else str = std::string("X")+CID()+std::string("B")+tostring(block);

while (str.length()<STREAMHEADERLEN) str=str+" ";
 writeconsoleln();
 writeconsole("---------------------------Stream Length:");
 writeconsole(len+STREAMHEADERLEN);
 writeconsoleln(str.c_str());

unsigned char buffer[256];
int bufcount=0,count=0;
for (count=0;count<str.length();count++){
  buffer[bufcount]=str[count];
  bufcount++;
}
if(bufcount>STREAMHEADERLEN){
  writeconsole("------------------------- ERROR   STREAM HEADER OVERFLOW ----------"); 
   writeconsole(bufcount);
}
while(bufcount<STREAMHEADERLEN){
  buffer[bufcount]=' ';
  bufcount++;
}

for (count=0;count<len;count++){
  buffer[bufcount]=data[count];
  bufcount++;
}

//memcpy(buffer, str.c_str(), 10);
//memcpy(buffer+10, data, len);

    CMsg m(str);
    std::string strfn((const char *)fileName);
    m.Parameters["FILE"]=strfn;
    m.Parameters["BLK"]=tostring(block);
    m.initArray(buffer,bufcount);   ///////////////////////////////////////////////////////////////////////////////////////////////////////////// FIX THIS
    addDataList(m); 
      writeconsoleln("..................................... Adding Picture Data to DataList .....................................");
      writeconsoleln(m.serialize());
}

void CPhone::onInitAvailable(int id) {   //Read from Phone add to queue

  writeconsoleln("..................................... On Init Available .....................................");
  unsigned char buff[BUFFER_LENGTH];
  bool ok = readUntil('\n', buff);
  if (!ok) return;

  CMsg m;
    m.Parameters["table"]="timephone";
    m.Parameters["init"]="OK"; 
    addTransmitList(m);

  setState("PLAY");
 
}

void CPhone::onTimeAvailable(int id) {   //Read from Phone  add to queue
  unsigned char timeStr[BUFFER_LENGTH];
  bool ok = readUntil('\n', timeStr);
  if (!ok) return;

  std::string str1=(char *)timeStr;
    CMsg m;
    m.Parameters["table"]="timephone";
    m.Parameters["time"]=str1; 
    addTransmitList(m);

 
}

void CPhone::onGpsAvailable(int id) {   //Read from Phone  add to queue
  unsigned char gpsStr[BUFFER_LENGTH];
  bool ok = readUntil('\n', gpsStr);
  if (!ok) return;


  std::string str;
  str=String((char *)gpsStr).c_str();
  int x=str.find(',');
  if (x+4<=str.size()){
    CMsg m;
    m.Parameters["table"]="gps";
    m.Parameters["lat"]=str.substr(0,x);
    m.Parameters["lon"]=str.substr(x+1,20);
    addTransmitList(m);
    

  }

}

void CPhone::onPhotoAvailable(int id) {    //Read from Phone  add to filename queue to go to comms
  unsigned char fileName[BUFFER_LENGTH];
  unsigned char fileSizeStr[BUFFER_LENGTH];
  long fileSize;
  bool ok = readUntil(',', fileName);
  if (!ok) return;
  ok = readUntil('\n', fileSizeStr);
  if (!ok) return;
  sscanf((char*)fileSizeStr, "%ld", &fileSize);

  //char msg[BUFFER_LENGTH];
  //sprintf(msg, "%s,%d", fileName, fileSize);
  std::string strfn((const char *)fileName);
  std::string strfs((const char *)fileSizeStr);
   CMsg m;
    m.Parameters["table"]="photos";
    m.Parameters["filename"]=strfn;
    m.Parameters["filesize"]=strfs;
    addTransmitList(m);
 

  /*char cmd[BUFFER_LENGTH];
  sprintf(cmd, "STREAM(%s,%d)", fileName, 0);
  sendSerial(cmd);*/
  //Done();
//  setState("COMPLETE");
}
 

void CPhone::onStreamAvailable(int id) {   //Read from Phone add to streamqueue
  unsigned char fileName[BUFFER_LENGTH];
  bool ok = readUntil(',', fileName);
  if (!ok) return;
  ok = waitForBytes(4);
  if (!ok) return;
  long block = (Serial1.read() << 8) + Serial1.read();
  char len = Serial1.read();
  unsigned char hasMore = Serial1.read();
  unsigned char data[len];
  for (int i = 0; i < len; i++) {
    ok = waitForBytes(1);
    if (!ok) {
      return;
    }
    data[i] = Serial1.read();
  }
  push_stream(id, fileName, block, len, hasMore, data);         //This is the output

  /*
  if (hasMore == 3) {         //This is the queue to get more data from the phone
    char cmd[50];
    memset(cmd, 0, sizeof(cmd));
    sprintf(cmd, "STREAM(%s,%ld+)", fileName, block+1);  //Seems to be stream command

    CMsg m(cmd);
    streamQueue.push(m);  
  }

  if (streamQueue.size() > 0) {   //Sends next request to phone
    sendSerial(streamQueue.front().Data().c_str());
    streamQueue.pop();
  }
  */
}



void CPhone::ProcessCommandQueue(){     //This is where the New Command is procressed and sent to the phone


if (commandQueue.size() > 0) {
  writeconsoleln("........................................ Sending Command to Phone .........................................");  
  CMsg cmsg =commandQueue.front();
  commandQueue.pop();

//  std::string bytes=cmsg.getMODE();    //Temporaty not using any params just seeing if CTIME works
  std::string bytes=cmsg.getACT();    //Temporaty not using any params just seeing if CTIME works
  writeconsoleln(cmsg.Data().c_str());
  writeconsoleln(bytes.c_str());
  received = false;
  
  if (bytes[0] == 'C') { //command
    std::string tmpstr=bytes.substr(1,200);  //Sends it to the Phone   Needs to start with 'C'
    sendSerial((char*)tmpstr.c_str());   //Sends it to the Phone  
  }
  else if (bytes[0] == 'A') { //acknowledgment from receiver
    waitingForAck = 0;
    /*
    char filename[16];
    for (int i = 0; i < 16; i++) {
      filename[i] = bytes[i+1];
      }
    bool sent = false;
    for (int i = 0; i < 64; i++) {
      for (int j = 0; j < 8; j++) {
        if ((bytes[i+1+16] & (1 << (7-j))) == 0) {
          char cmd[BUFFER_LENGTH];
          memset(cmd, 0, sizeof(cmd));
          sprintf(cmd, "STREAM(%s,%ld)", filename, i*8 + j);
          if (!sent) {
            sendSerial(cmd);        //Sends it to the Phone
            sent = true;
          }
          else {
            std::string s=cmd;
            CMsg m(s);
            streamQueue.push(m);
          }
        }
      }
    }
    */
  } 
}
//Play();
setState("PLAY");

}


 
void CPhone::ReceivedPacket() {  //Any Comments to Serial Port go right back to the PHONE!!!!!  Screws it up
//writeconsoleln(F("o"));
 
  if (Serial1.available() > 0) {   //Reads data from phone.  Takes ID and MessageType and uses that to call the appropriate function to read from phone and if result is good adds it to the "queue"
    writeconsoleln(" ------------------------------- Phone loop Reading Data ----------------------------------------------------------------------------------------------------------------");
    unsigned char msgIdStr[BUFFER_LENGTH];
    int msgId;
    char msgType;
    bool ok = readUntil(',', msgIdStr);
    if (!ok) return;
    sscanf((char*)msgIdStr, "%d", &msgId);
    ok = waitForBytes(1);
    if (!ok) return;
    msgType = Serial1.read();
  
    switch (msgType) {
      case 'I':
        onInitAvailable(msgId);
        break;
      case 'T':
        onTimeAvailable(msgId);  
        break;
      case 'G':
        onGpsAvailable(msgId);
        break;
      case 'P':
        onPhotoAvailable(msgId);
        break;
      case 'S':
        onStreamAvailable(msgId);
        break;
    }
  }

}


void CPhone::SetPhoneReceive(){}

void CPhone::TransmitPacket(CMsg &m){
  commandQueue.push(m);
}   

void CPhone::loop() {    
  ReceivedPacket();
  ProcessCommandQueue();
}
