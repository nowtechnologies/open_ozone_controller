float ozoneLevel(){
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
          mainMenu->getLCD()->print(F(" ppm / "));
          mainMenu->getLCD()->print(int(sensorPacket.temperature));
          mainMenu->getLCD()->print(F("C"));
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
  if (SPIozoneSensorPresent || ozoneMonitorConnected)
  {
    mainMenu->getLCD()->clear();
    mainMenu->getLCD()->setCursor(0,0);
    mainMenu->getLCD()->print(F("Adjust baseline"));
    while (buttonState != btnLEFT) {
        buttonState = read_LCD_buttons();
        if (SPIozoneSensorPresent)
        {
          ozoneSensor.read();
          ozoneSensor.getO3();
          clearSecondLcdRow();
          mainMenu->getLCD()->print(F("Zero: "));
          mainMenu->getLCD()->print(1.0-ozoneSensor.getRatio());
          delay(100);
        }
        else if (ozoneMonitorConnected)
        {
          checkIncomingSerial();
          clearSecondLcdRow();
          mainMenu->getLCD()->print(F("Zero: "));
          mainMenu->getLCD()->print(1.0-sensorPacket.ratio); // there are no threads !
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
