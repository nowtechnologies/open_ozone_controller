#ifndef _CONTROLLER_SETTINGS_ACTION_HEADER_
#define _CONTROLLER_SETTINGS_ACTION_HEADER_

// TODO: refactor

/*
bool settingsAction(uint8_t *value, String topic, String unit)
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print(topic);
  mainMenu->getLCD()->setCursor(0,1);
  uint8_t vp = value;
  mainMenu->getLCD()->print(vp);
  mainMenu->getLCD()->print(unit);
  delay(500);
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
      if (buttonState != lastButton)
      {
        switch (buttonState)
        {
        case btnDOWN :
          value--;
          if (value < 0 ) value = 0;
          break;
        case btnUP :
          value++;
          if (value > 255 ) value = 255;
          break;
        case btnRIGHT :
          clearSecondLcdRow();
          uint8_t vp = value;
          mainMenu->getLCD()->print(vp);
          mainMenu->getLCD()->print(unit);
          displaySaved();
          delay(500);
          return true;
          break;
        }
        lastButton = buttonState;
        clearSecondLcdRow();
        uint8_t vp = value;
        mainMenu->getLCD()->print(vp);
        mainMenu->getLCD()->print(unit);
      }
  }
  return false;
}
*/

void deconTimeAction()
{
//  if (settingsAction(&deconTime,"DeconTime:"," min")) config.storeDeconTime(deconTime);
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("Decon. Time:");
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(deconTime);
  mainMenu->getLCD()->print(" min");
  delay(500);
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
      if (buttonState != lastButton)
      {
        switch (buttonState)
        {
        case btnDOWN :
          deconTime--;
          if (deconTime < 0 ) deconTime = 0;
          break;
        case btnUP :
          deconTime++;
          if (deconTime > 255 ) deconTime = 255;
          break;
        case btnRIGHT :
          config.storeDeconTime(deconTime);
          displaySaved();
          break;
        }
        lastButton = buttonState;
        clearSecondLcdRow();
        mainMenu->getLCD()->print(deconTime);
        mainMenu->getLCD()->print(" min");
      }
  }
}

void killLevelAction()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("O3 Kill Level:");
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(killLevel);
  mainMenu->getLCD()->print(" ppm");
  delay(500);
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
      if (buttonState != lastButton)
      {
        switch (buttonState)
        {
        case btnDOWN :
          killLevel--;
          if (killLevel < 0 ) killLevel = 0;
          break;
        case btnUP :
          killLevel++;
          if (killLevel > 255 ) killLevel = 255;
          break;
        case btnRIGHT :
          config.storeKillLevel(killLevel);
          displaySaved();
          break;
        }
        lastButton = buttonState;
        clearSecondLcdRow();
        mainMenu->getLCD()->print(killLevel);
        mainMenu->getLCD()->print(" ppm");
      }
  }
}

void controlThresholdAction()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("Threshold:");
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(ctrlThreshold);
  mainMenu->getLCD()->print(" ppm");
  delay(500);
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
      if (buttonState != lastButton)
      {
        switch (buttonState)
        {
        case btnDOWN :
          ctrlThreshold--;
          if (ctrlThreshold < 0 ) ctrlThreshold = 0;
          break;
        case btnUP :
          ctrlThreshold++;
          if (ctrlThreshold > 255 ) ctrlThreshold = 255;
          break;
        case btnRIGHT :
          config.storeKillLevel(ctrlThreshold);
          displaySaved();
          break;
        }
        lastButton = buttonState;
        clearSecondLcdRow();
        mainMenu->getLCD()->print(ctrlThreshold);
        mainMenu->getLCD()->print(" ppm");
      }
  }
}

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

void lockInstalledAction()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print(F("Lock present?"));
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(lockInstalled?"yes":"no");
  delay(500);
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
      if (buttonState != lastButton)
      {
        switch (buttonState)
        {
        case btnDOWN :
          lockInstalled = false;
          break;
        case btnUP :
          lockInstalled = true;
          break;
        case btnRIGHT :
          config.storeLockInstalled(lockInstalled);
          displaySaved();
          break;
        }
        lastButton = buttonState;
        clearSecondLcdRow();
        mainMenu->getLCD()->print(lockInstalled?"yes":"no");
      }
  }
}

void serialEchoAction()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print(F("Enable echo?"));
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(echoEnabled?"yes":"no");
  delay(500);
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
      if (buttonState != lastButton)
      {
        switch (buttonState)
        {
        case btnDOWN :
          echoEnabled = false;
          break;
        case btnUP :
          echoEnabled = true;
          break;
        case btnRIGHT :
          config.storeEchoState(echoEnabled);
          displaySaved();
          break;
        }
        lastButton = buttonState;
        clearSecondLcdRow();
        mainMenu->getLCD()->print(echoEnabled?"yes":"no");
      }
  }
}
#endif
