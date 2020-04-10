#ifndef _CONTROLLER_BUTTON_UTILS_HEADER_
#define _CONTROLLER_BUTTON_UTILS_HEADER_

enum buttons
{
  btnRIGHT,
  btnUP,
  btnDOWN,
  btnLEFT,
  btnTIMER,
  btnNONE
};

int lastButton = btnNONE;

int read_LCD_buttons()
{
  int adc_key_in = analogRead(buttonsPin);
  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   { wait(200); return btnRIGHT;}
  if (adc_key_in < 195)  { wait(200); return btnUP;}
  if (adc_key_in < 380)  { wait(200); return btnDOWN;}
  if (adc_key_in < 555)  { wait(200); return btnLEFT;}
  if (adc_key_in < 790)  { wait(200); return btnTIMER;}
  return btnNONE;
}

void holdUntilEscape()
{
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
      checkIncomingSerial();
      statusReport();
  }
}

int waitForButtonPress()
{
  int buttonState = btnNONE;
  while (buttonState == btnNONE) {
      buttonState = read_LCD_buttons();
      statusReport();
  }
  return buttonState;
}

#endif
