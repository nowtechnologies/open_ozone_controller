
void ozoneDisplayAction()
{
  int buttonState = btnNONE;
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("Ozone level:");
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
      if (SPIozoneSensorPresent)
      {
        ozoneSensor.read();
        clearSecondLcdRow();
        mainMenu->getLCD()->print(ozoneSensor.getO3());
        mainMenu->getLCD()->print(" ppm");
        delay(200);
      }
      else {
        clearSecondLcdRow();
        mainMenu->getLCD()->print(sensorPacket.ozonePPM);
        mainMenu->getLCD()->print(" ppm");
        delay(200);
      }
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
      mainMenu->getLCD()->print("Adjust baseline:");
      clearSecondLcdRow();
      mainMenu->getLCD()->print(1.0-ozoneSensor.getRatio());
      delay(200);
    }
  }
  else {
    mainMenu->getLCD()->clear();
    mainMenu->getLCD()->setCursor(0,0);
    mainMenu->getLCD()->print("No SPI O3 Sensor");
  }
}
