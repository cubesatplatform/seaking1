#include "system_example.h"
#include "consoleio.h"


CExample::CExample(){
  Name("EXAMPLE");
  setInterval(3000);
  Forever(true);
}

void CExample::setup(){
  lcount=0;
}

void CExample::loop(){
  CMsg m;

  
  m.setSYS("IRX1");
  m.setACT("RUNONCE");
  m.setParameter("OUTPUT","D");
  
  addMessageList(m);
  }
