#ifndef _CONTROLLER_GENERATOR_ACTION_HEADER_
#define _CONTROLLER_GENERATOR_ACTION_HEADER_

enum peripherals{
  generator,
  blower,
  humidifier,
  decomposer
};

String  nameOfPeripherals[] = {"Ozone generator","Blower","Humidifier","Decomposer"};
uint8_t portPin[] = {generatorPin, fanEnablePin, humidifierPin, decomposerPin};
bool    portEnabled[] = {false, false, false, false};

void testAction(int p)
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print(nameOfPeripherals[p]);
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(portEnabled[p]?"ON":"OFF");
#ifdef DEBUG
  Serial.println(nameOfPeripherals[p]);
  Serial.println(portEnabled[p]?"ON":"OFF");
#endif
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
#ifdef DEBUG
		Serial.println(nameOfPeripherals[p]);
		Serial.println(portEnabled[p]?"ON":"OFF");
#endif
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


#endif
