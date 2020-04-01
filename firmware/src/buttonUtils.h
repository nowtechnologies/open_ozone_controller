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
#ifdef DEBUG
  if (Serial.available() > 0) {
    int ch = Serial.read();
	switch (ch) {
		case 'U':
			Serial.println("[UP]");
			return btnUP;
		case 'D':
			Serial.println("[DOWN]");
			return btnDOWN;
		case 'R':
			Serial.println("[RIGHT]");
			return btnRIGHT;
		case 'L':
			Serial.println("[LEFT]");
			return btnLEFT;
		case 'T':
			Serial.println("[TIMER]");
			return btnTIMER;
		default:
			return btnNONE;
	}
  } else {
	return btnNONE;
  }
#endif
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
