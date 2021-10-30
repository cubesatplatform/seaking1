#include "state_detumble.h"


CDetumbleState::CDetumbleState() {
  _name="DETUMBLE";

};

CDetumbleState::~CDetumbleState() {};

void CDetumbleState::setup() {};
void CDetumbleState::stateMsg(CMsg &msg){_statemsg=msg;};
void CDetumbleState::enter() { CStateObj::enter();writeconsole("Enter Detumble"); }
void CDetumbleState::exit() { CStateObj::exit();writeconsole("Exit Detumble"); }
