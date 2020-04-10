#ifndef _CONTROLLER_SETTINGS_ACTION_HEADER_
#define _CONTROLLER_SETTINGS_ACTION_HEADER_

int settingsAction(uint16_t value, uint8_t stepSize, uint16_t maxValue, String topic, String unit = NULL)
{
  displayTopic(topic);
  displayValue(value, unit);
  delay(500);
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
      if (buttonState != lastButton)
      {
        switch (buttonState)
        {
        case btnDOWN :
          value-=stepSize;
          if (value < 0 ) value = 0;
          break;
        case btnUP :
          value+=stepSize;
          if (value > maxValue ) value = maxValue;
          break;
        case btnRIGHT :
          displaySaved();
          displayValue(value, unit);
          delay(1000);
          return value;
          break;
        }
        lastButton = buttonState;
        displayValue(value, unit);
      }
  }
  return -1;
}

int choiceAction(bool choice, String topic)
{
  displayTopic(topic);
  displayChoice(choice);
  delay(500);
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
      if (buttonState != lastButton)
      {
        switch (buttonState)
        {
        case btnDOWN :
          choice = false;
          break;
        case btnUP :
          choice = true;
          break;
        case btnRIGHT :
          displaySaved();
          displayChoice(choice);
          delay(1000);
          return choice;
          break;
        }
        lastButton = buttonState;
        displayChoice(choice);
      }
  }
  return -1;
}

void deconTimeAction()
{
  int v = settingsAction(deconTime, 1, 255, F("Decon. Time:"), F("min"));
  if (v>0) {
    deconTime = v;
    config.storeDeconTime(deconTime);
  }
}

void generatorCapacityAction()
{
  int v = settingsAction(generatorCapacity, 100, 10000, F("Gen. Capacity:"), F("mg/h"));
  if (v>0) {
    generatorCapacity = v;
    config.storeGeneratorCapacity(generatorCapacity);
  }
}

void chamberVolumeAction()
{
  int v = settingsAction(chamberVolume, 10, 1000, F("Chamber volume:"), F("liter"));
  if (v>0) {
    chamberVolume = v;
    config.storeChamberVolume(chamberVolume);
  }
}

void killLevelAction()
{
  int v = settingsAction(killLevel, 1, 255, F("O3 Kill Level:"), F("ppm"));
  if (v>0) {
    killLevel = v;
    config.storeKillLevel(killLevel);
  }
}

void controlThresholdAction()
{
  int v = settingsAction(ctrlThreshold, 1, 255, F("Threshold:"), F("ppm"));
  if (v>0) {
    ctrlThreshold = v;
    config.storeControlThreshold(ctrlThreshold);
  }
}

void brightnessAction()
{
  int v = settingsAction(lcdBrightness, 1, 255, F("LCD brightness:"), F("pwm"));
  if (v>0) {
    lcdBrightness = v;
    config.storeBrightness(lcdBrightness);
  }
}

void lockInstalledAction()
{
  int v = choiceAction(lockInstalled, F("Lock present?"));
  if (v>-1) {
    lockInstalled = bool(v);
    config.storeLockInstalled(lockInstalled);
  }
}

void serialLogAction(){
  int v = choiceAction(LogEnabled, F("Enable log?"));
  if (v>-1) {
    LogEnabled = bool(v);
    config.storeLogState(LogEnabled);
  }
}

#endif
