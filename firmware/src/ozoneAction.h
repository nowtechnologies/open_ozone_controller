float ozoneLevel(){
  if (SPIozoneSensorPresent)
  {
    ozoneSensor.read();
    return ozoneSensor.getO3();
  }
  else if (ozoneMonitorConnected)
  {
    checkIncomingSerial();
    return sensorPacket.ozonePPM; // requires buffer check
  }
  else return -1;
}

void ozoneDisplayAction()
{
  int buttonState = btnNONE;
  if (SPIozoneSensorPresent || ozoneMonitorConnected)
  {
    displayTopic(F("Ozone level:"));
    while (buttonState != btnLEFT) {
        buttonState = read_LCD_buttons();

        if (SPIozoneSensorPresent)
        {
          ozoneSensor.read();
          if (millis()%100==0)
          {
            displayValue(ozoneSensor.getO3(),F("ppm"));
          }
        }
        else if (ozoneMonitorConnected)
        {
          checkIncomingSerial();
          if (millis()%100==0)
          {
            clearSecondLcdRow();
            mainMenu->getLCD()->print(sensorPacket.ozonePPM);
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
  if (SPIozoneSensorPresent || ozoneMonitorConnected)
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
