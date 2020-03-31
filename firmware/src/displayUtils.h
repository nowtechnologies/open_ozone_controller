#ifndef _CONTROLLER_DISPLAY_UTILS_
#define _CONTROLLER_DISPLAY_UTILS_

void clearSecondLcdRow(){
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print("               ");
  mainMenu->getLCD()->setCursor(0,1);
}

void displaySaved()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("Saved:");
}

#endif
