#ifndef _CONTROLLER_DISPLAY_UTILS_
#define _CONTROLLER_DISPLAY_UTILS_

void clearFirstLcdRow(){
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print(F("               "));
  mainMenu->getLCD()->setCursor(0,0);
}

void clearSecondLcdRow(){
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(F("               "));
  mainMenu->getLCD()->setCursor(0,1);
}

void displaySaved()
{
  clearFirstLcdRow();
  mainMenu->getLCD()->print(F("Saved:"));
}

void displayValue(uint16_t value, String unit)
{
  clearSecondLcdRow();
  mainMenu->getLCD()->print(value);
  mainMenu->getLCD()->print(F(" "));
  mainMenu->getLCD()->print(unit);
}

void displayTopic(String topic)
{
  clearFirstLcdRow();
  mainMenu->getLCD()->print(topic);
}

void displayChoice(bool choice)
{
  clearSecondLcdRow();
  mainMenu->getLCD()->print(choice?"yes":"no");
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
