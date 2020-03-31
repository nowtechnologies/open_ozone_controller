#include <Arduino.h>
#include <LiquidCrystal.h>
#include <LCDMenu.h>
#include <LCDMenuItem.h>
#include <Storage.h>
#include <Timer.h>

// hardcoded version
#define fw_major  0
#define fw_minor  1
#define fw_fix    2

// pinmap
#define fanEnablePin  0
#define safeSignPin   1 // also lock disable
#define chipSelect1   2
#define chipSelect2   3
#define lcdData4Pin   4
#define lcdData5Pin   5
#define lcdData6Pin   6
#define lcdData7Pin   7
#define lcdResetPin   8
#define lcdEnablePin  9
#define lcdBrightPin  10
//SPI: 11 - 12 - 13
#define buttonsPin    A0
// A1 not used
#define generatorPin  A3
#define decomposerPin A4
#define humidifierPin A5

bool generatorEnabled = false;

enum buttons
{
  btnRIGHT,
  btnUP,
  btnDOWN,
  btnLEFT,
  btnTIMER,
  btnNONE
};

LiquidCrystal* LCD;
LCDMenu* mainMenu;
Storage config;
Timer   timer;

int lastButton = 0;
int lcdBrightness = 255;

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

void nada(){}

void holdUntilEscape()
{
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
  }
}

void clearSecondLcdRow(){
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print("               ");
  mainMenu->getLCD()->setCursor(0,1);
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
        clearSecondLcdRow();
        mainMenu->getLCD()->print(lcdBrightness);
        analogWrite(lcdBrightPin, lcdBrightness);
      }
  }
}

void generatorAction()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("Ozone generator");
  delay(500);
  int buttonState = btnNONE;
  while (buttonState != btnLEFT) {
      buttonState = read_LCD_buttons();
      if (buttonState != lastButton)
      {
        switch (buttonState)
        {
        case btnDOWN :
            generatorEnabled = false;
          break;
        case btnUP :
            generatorEnabled = true;
          break;
        }
        lastButton = buttonState;
        clearSecondLcdRow();
        mainMenu->getLCD()->print(generatorEnabled?"ON":"OFF");
        digitalWrite(generatorPin, generatorEnabled);
      }
  }
}

uint32_t lastTime = 0;

void timerAction(){
  int buttonState = btnNONE;
  uint16_t timerSeconds = 10;
  boolean timerStarted = false;
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("Start timer: ");
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(timerSeconds);
  mainMenu->getLCD()->print(" sec");
  while (buttonState != btnLEFT) {

      buttonState = read_LCD_buttons();
      if (buttonState != lastButton && !timerStarted)
      {
        switch (buttonState)
        {
        case btnDOWN :
            timerSeconds--;
            if (timerSeconds < 0) timerSeconds = 0;
        break;
        case btnUP :
            timerSeconds++;
            if (timerSeconds > 65535) timerSeconds = 65535;
        break;
        case btnRIGHT :
            timer.set(timerSeconds*1000);
            timerStarted = true;
            mainMenu->getLCD()->clear();
            mainMenu->getLCD()->setCursor(0,0);
            mainMenu->getLCD()->print("Time left: ");
            digitalWrite(generatorPin, HIGH);
        break;
        }
        lastButton = buttonState;
        clearSecondLcdRow();
        mainMenu->getLCD()->print(timerSeconds);
        mainMenu->getLCD()->print(" sec");
      }

      if (timerStarted)
      {
        uint32_t remaining = round(timer.TimeRemaining()/1000);
        if (!timer.poll() && lastTime != remaining)
        {
          clearSecondLcdRow();
          mainMenu->getLCD()->print(remaining);
          mainMenu->getLCD()->print(" sec");
          lastTime = remaining;
        }
        if (timer.poll()) {
          digitalWrite(generatorPin, LOW);
        }
      }

  }
  digitalWrite(generatorPin, LOW);
}

void setup()
{
  Serial.begin(9600);
  // pinMode(fanEnablePin, OUTPUT);  digitalWrite(fanEnablePin, LOW);
  // pinMode(safeSignPin, OUTPUT);   digitalWrite(safeSignPin, LOW);
  pinMode(generatorPin, OUTPUT);  digitalWrite(generatorPin, LOW);
  pinMode(decomposerPin, OUTPUT); digitalWrite(decomposerPin, LOW);
  pinMode(humidifierPin, OUTPUT); digitalWrite(humidifierPin, LOW);

  LCD = new LiquidCrystal(lcdResetPin, lcdEnablePin, lcdData4Pin, lcdData5Pin, lcdData6Pin, lcdData7Pin);
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
  newItem->setAction(&generatorAction);
  mainMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem("Set timer");
  newItem->setAction(&timerAction);
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
    case btnTIMER :
      timerAction();
      break;
    }
    mainMenu->display();
    lastButton = buttonState;
  }
}
