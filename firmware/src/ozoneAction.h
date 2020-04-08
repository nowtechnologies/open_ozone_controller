float getOzoneLevel(){
  if (SPIozoneSensorPresent)
  {
    ozoneSensor.read();
    return ozoneSensor.getO3();
  }
  else if (ozoneMonitorConnected)
  {
    return sensorPacket.ozonePPM; // requires buffer check
  }
  else return -1;
}

void ozoneDisplayAction()
{
  int buttonState = btnNONE;
  if (SPIozoneSensorPresent || ozoneMonitorConnected)
  {
    mainMenu->getLCD()->clear();
    mainMenu->getLCD()->setCursor(0,0);
    mainMenu->getLCD()->print(F("Ozone level:"));
    while (buttonState != btnLEFT) {
        buttonState = read_LCD_buttons();
        if (SPIozoneSensorPresent)
        {
          ozoneSensor.read();
          clearSecondLcdRow();
          mainMenu->getLCD()->print(ozoneSensor.getO3());
          mainMenu->getLCD()->print(F(" ppm"));
          delay(100);
        }
        else if (ozoneMonitorConnected)
        {
          checkIncomingSerial();
          clearSecondLcdRow();
          mainMenu->getLCD()->print(sensorPacket.ozonePPM); // there are no threads !
          mainMenu->getLCD()->print(F(" ppm"));
          delay(100);
        }
    }
  } else {
    mainMenu->getLCD()->clear();
    mainMenu->getLCD()->setCursor(0,0);
    mainMenu->getLCD()->print(F("No Sensor"));
    holdUntilEscape();
  }
}

void ozoneCalibrationAction()
{
  int buttonState = btnNONE;
  if (SPIozoneSensorPresent)
  {
    while (buttonState != btnLEFT) {
      ozoneSensor.read();
      ozoneSensor.getO3();
      buttonState = read_LCD_buttons();
      mainMenu->getLCD()->clear();
      mainMenu->getLCD()->setCursor(0,0);
      mainMenu->getLCD()->print(F("Adjust baseline:"));
      clearSecondLcdRow();
      mainMenu->getLCD()->print(1.0-ozoneSensor.getRatio());
      delay(200);
    }
  }
  else {
    mainMenu->getLCD()->clear();
    mainMenu->getLCD()->setCursor(0,0);
    mainMenu->getLCD()->print(F("No SPI O3 Sensor"));
    holdUntilEscape();
  }
}
