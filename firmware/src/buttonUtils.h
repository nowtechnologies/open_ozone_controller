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
  if (adc_key_in < 50)   { delay(100); return btnRIGHT;}
  if (adc_key_in < 195)  { delay(100); return btnUP;}
  if (adc_key_in < 380)  { delay(100); return btnDOWN;}
  if (adc_key_in < 555)  { delay(100); return btnLEFT;}
  if (adc_key_in < 790)  { delay(100); return btnTIMER;}
  return btnNONE;
}

void holdUntilEscape()
{
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
  }
}

#endif
