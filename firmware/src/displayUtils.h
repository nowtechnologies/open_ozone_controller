#ifndef _CONTROLLER_DISPLAY_UTILS_
#define _CONTROLLER_DISPLAY_UTILS_

void clearSecondLcdRow(){
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(F("               "));
  mainMenu->getLCD()->setCursor(0,1);
}

void displaySaved()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print(F("Saved:"));
}

// void displayPOST(){
//   mainMenu->getLCD()->clear();
//   mainMenu->getLCD()->setCursor(0,0);
//   mainMenu->getLCD()->print(SPIhumiditySensorPresent?"BMP280........OK":"BMP280........NC");
//   mainMenu->getLCD()->setCursor(0,1);
//   mainMenu->getLCD()->print(SPIozoneSensorPresent?"MQ131.........OK":"MQ131.........NC");
//   delay(1000);
// }

#endif
