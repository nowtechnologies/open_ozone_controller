void ozoneAction()
{
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
    buttonState = read_LCD_buttons();
    mainMenu->getLCD()->clear();
    mainMenu->getLCD()->setCursor(0,0);
    mainMenu->getLCD()->print("Ozone level:");
    mainMenu->getLCD()->setCursor(0,1);
    mainMenu->getLCD()->print(analogRead(A15));
    delay(200);
  }
}
