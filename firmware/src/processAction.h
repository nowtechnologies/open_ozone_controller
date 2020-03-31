#ifndef _CONTROLLER_PROCESS_ACTION_HEADER_H_
#define _CONTROLLER_PROCESS_ACTION_HEADER_H_

void processAction()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("Decontamination");
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print("in progress...");
  holdUntilEscape();
}

#endif
