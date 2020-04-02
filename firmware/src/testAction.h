#ifndef _CONTROLLER_GENERATOR_ACTION_HEADER_
#define _CONTROLLER_GENERATOR_ACTION_HEADER_

enum peripherals{
  generator,
  blower,
  decomposer,
  humidifier,
  lock
};

String  nameOfPeripherals[] = {"Ozone generator","Blower","Decomposer","Humidifier","Lock"};
uint8_t portPin[] = {generatorPin, fanEnablePin, decomposerPin, humidifierPin, safeSignPin};
bool    portEnabled[] = {false, false, false, false, false};

void testAction(int p)
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print(nameOfPeripherals[p]);
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(portEnabled[p]?"ON":"OFF");
  delay(500);
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
      if (buttonState != lastButton)
      {
        switch (buttonState)
        {
        case btnDOWN :
            portEnabled[p] = false;
          break;
        case btnUP :
            portEnabled[p] = true;
          break;
        }
        lastButton = buttonState;
        clearSecondLcdRow();
        mainMenu->getLCD()->print(portEnabled[p]?"ON":"OFF");
        digitalWrite(portPin[p], portEnabled[p]);
      }
  }
}

void generatorTestAction(){
  testAction(generator);
}
void blowerTestAction(){
  testAction(blower);
}
void humidifierTestAction(){
  testAction(humidifier);
}
void decomposerTestAction(){
  testAction(decomposer);
}
void lockTestAction(){
  testAction(lock);
}


#endif
