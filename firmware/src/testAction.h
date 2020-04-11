#ifndef _CONTROLLER_GENERATOR_ACTION_HEADER_
#define _CONTROLLER_GENERATOR_ACTION_HEADER_

void testAction(int p)
{
  displayInfo(nameOfPeripherals[p],portEnabled[p]?"ON":"OFF");
  wait(500);
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
        updatePorts();
      }
    checkIncomingSerial(); 
    statusReport();
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
