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

void displayPOST(){
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print(humiditySensorPresent?"AM2320........OK":"AM2320......FAIL");
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(ozoneSensorPresent?"MQ131.........OK":"MQ131.......FAIL");
  delay(2000);
}

#endif
