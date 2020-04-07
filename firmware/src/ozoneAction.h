boolean ozoneSensorCalibrating = false;

void ozoneDisplayAction()
{
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
    ozoneSensor.read();
    buttonState = read_LCD_buttons();
    mainMenu->getLCD()->clear();
    mainMenu->getLCD()->setCursor(0,0);
    mainMenu->getLCD()->print("Ozone level:");
    clearSecondLcdRow();
    mainMenu->getLCD()->print(ozoneSensor.getO3());
    mainMenu->getLCD()->print(" ppm");
    delay(200);
  }
}

void ozoneCalibrationAction()
{
  int buttonState = btnNONE;
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
