float ozoneLevel(){
  return sensorPacket.ozonePPM;
}

void ozoneDisplayAction()
{
  int buttonState = btnNONE;
  if (ozoneMonitorConnected)
  {
    displayTopic(F("Ozone level:"));
    while (buttonState != btnLEFT) {
        buttonState = read_LCD_buttons();
        if (ozoneMonitorConnected)
        {
          checkIncomingSerial();
          if (millis()%100==0)
          {
            clearSecondLcdRow();
            mainMenu->getLCD()->print(ozoneLevel());
            mainMenu->getLCD()->print(F(" ppm / "));
            mainMenu->getLCD()->print(int(sensorPacket.temperature));
            mainMenu->getLCD()->print(F("C"));
          }
        }
        statusReport();
    }
  } else {
    displayWarning(F("No Sensor"));
    holdUntilEscape();
  }
}

void ozoneCalibrationAction()
{
  int buttonState = btnNONE;
  if (ozoneMonitorConnected)
  {
    displayTopic(F("Adjust baseline"));
    while (buttonState != btnLEFT) {
        buttonState = read_LCD_buttons();
        if (millis()%100==0)
        {
          clearSecondLcdRow();
          mainMenu->getLCD()->print(F("Zero: "));
          mainMenu->getLCD()->print(1.0-ozoneLevel());
        }
        statusReport();
    }
  } else {
    displayWarning(F("No Sensor"));
    holdUntilEscape();
  }
}
