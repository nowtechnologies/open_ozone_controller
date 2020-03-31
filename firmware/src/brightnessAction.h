#ifndef _CONTROLLER_LCD_BRIGHTNESS_ACTION_HEADER_
#define _CONTROLLER_LCD_BRIGHTNESS_ACTION_HEADER_

int lcdBrightness = 255;

void brightnessAction()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("LCD brightness:");
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(lcdBrightness);
  delay(500);
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
      if (buttonState != lastButton)
      {
        switch (buttonState)
        {
        case btnDOWN :
          lcdBrightness-=10;
          if (lcdBrightness < 0 ) lcdBrightness = 0;
          break;
        case btnUP :
          lcdBrightness+=10;
          if (lcdBrightness > 255 ) lcdBrightness = 255;
          break;
        case btnRIGHT :
          config.storeBrightness(lcdBrightness);
          displaySaved();
          break;
        }
        lastButton = buttonState;
        clearSecondLcdRow();
        mainMenu->getLCD()->print(lcdBrightness);
        analogWrite(lcdBrightPin, lcdBrightness);
      }
  }
}

#endif
