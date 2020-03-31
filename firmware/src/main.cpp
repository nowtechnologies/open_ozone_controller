#include <Arduino.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <LCDMenu.h>
#include <LCDMenuItem.h>
#include <Storage.h>

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnTIMER  4
#define btnNONE   5
#define lcdBrightPin 10
#define fw_major  0
#define fw_minor  1
#define fw_fix    2

LiquidCrystal* LCD;
LCDMenu* mainMenu;
Storage config;

int lastButton = 0;
int lcdBrightness = 255;

int read_LCD_buttons()
{
  int adc_key_in = analogRead(0);
  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnTIMER;
  return btnNONE;
}

void nada(){}

void holdUntilEscape()
{
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
  }
}

void displaySaved()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("Saved:");
}

void settingsAction()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("Decontamination");
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print("in progress...");
  holdUntilEscape();
}

void firmwareInfoAction()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("Firmware version:");
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print("v");
  mainMenu->getLCD()->print(fw_major);
  mainMenu->getLCD()->print(".");
  mainMenu->getLCD()->print(fw_minor);
  mainMenu->getLCD()->print(".");
  mainMenu->getLCD()->print(fw_fix);
  holdUntilEscape();
}

void brightnessAction()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("LCD brightness:");
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(lcdBrightness);
  delay(500);
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
      if (buttonState != lastButton)
      {
        switch (buttonState)
        {
        case btnDOWN :
          lcdBrightness-=10;
          if (lcdBrightness < 0 ) lcdBrightness = 0;
          break;
        case btnUP :
          lcdBrightness+=10;
          if (lcdBrightness > 255 ) lcdBrightness = 255;
          break;
        case btnRIGHT :
          config.storeBrightness(lcdBrightness);
          displaySaved();
          break;
        }
        lastButton = buttonState;
        mainMenu->getLCD()->setCursor(0,1);
        mainMenu->getLCD()->print("    ");
        mainMenu->getLCD()->setCursor(0,1);
        mainMenu->getLCD()->print(lcdBrightness);
        analogWrite(lcdBrightPin, lcdBrightness);
      }
  }
}

void setup()
{
  LCD = new LiquidCrystal(8, 9, 4, 5, 6, 7);
  LCD->begin(16,2);
  LCD->clear();

  mainMenu     = new LCDMenu("Main Menu", LCD);
  LCDMenuItem *newItem;

  newItem = new LCDMenuItem("Start");
  newItem->setAction(&settingsAction);
  mainMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem("Measure");
  newItem->setAction(&nada);
  mainMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem("Set generator");
  newItem->setAction(&nada);
  mainMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem("Set chamber");
  newItem->setAction(&nada);
  mainMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem("Set brightness");
  newItem->setAction(&brightnessAction);
  mainMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem("Firmware info");
  newItem->setAction(&firmwareInfoAction);
  mainMenu->addMenuItem(newItem);

  lcdBrightness = config.brightness();
  pinMode(lcdBrightPin, OUTPUT);
  analogWrite(lcdBrightPin, lcdBrightness);
  mainMenu->display();
}


void loop()
{
  int buttonState = read_LCD_buttons();
  if (buttonState != lastButton)
  {
    mainMenu->getLCD()->setCursor(0,0);
    switch (buttonState)
    {
    case btnDOWN :
      mainMenu->getLCD()->print(mainMenu->next()->getName());
      break;
    case btnUP :
      mainMenu->getLCD()->print(mainMenu->prev()->getName());
      break;
    case btnRIGHT :
      mainMenu->selectOption();
      break;
    }
    mainMenu->display();
    lastButton = buttonState;
  }
}
