void ozoneAction()
{
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
    ozoneSensor.readLong();
    buttonState = read_LCD_buttons();
    mainMenu->getLCD()->clear();
    mainMenu->getLCD()->setCursor(0,0);
    mainMenu->getLCD()->print("Ozone level:");
    clearSecondLcdRow();
    mainMenu->getLCD()->print(ozoneSensor.getOzonePPM());
    mainMenu->getLCD()->print(" ppm");
    delay(200);
  }
}
