#ifndef _CONTROLLER_GENERATOR_ACTION_HEADER_
#define _CONTROLLER_GENERATOR_ACTION_HEADER_

bool generatorEnabled = false;

void generatorAction()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("Ozone generator");
  delay(500);
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
      if (buttonState != lastButton)
      {
        switch (buttonState)
        {
        case btnDOWN :
            generatorEnabled = false;
          break;
        case btnUP :
            generatorEnabled = true;
          break;
        }
        lastButton = buttonState;
        clearSecondLcdRow();
        mainMenu->getLCD()->print(generatorEnabled?"ON":"OFF");
        digitalWrite(generatorPin, generatorEnabled);
      }
  }
}

#endif
