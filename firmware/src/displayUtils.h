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

void displayInfo(String firstRow, String secondRow = NULL){
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print(firstRow);
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(secondRow);
}

void displayWarning(String warning){
  displayInfo(F("WARNING!"),warning);
}

#endif
