// compile time switch
// #define DEBUG

// Libraries
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <LCDMenu.h>
#include <LCDMenuItem.h>
#include <Storage.h>
#include <Timer.h>
#include <AM2320.h>

// Globals
bool ozoneSensorPresent    = false;
bool humiditySensorPresent = false;
AM2320 humiditySensor(&Wire);
LiquidCrystal* LCD;
LCDMenu* activeMenu;
LCDMenu* mainMenu;
LCDMenu* settingsMenu;
Storage config;
Timer   timer;

// Headers
#include "version.h"
#include "pinMap.h"
#include "buttonUtils.h"
#include "displayUtils.h"
#include "timerAction.h"
#include "fwInfoAction.h"
#include "humidityAction.h"
#include "brightnessAction.h"
#include "generatorAction.h"
#include "processAction.h"
#include "settingsAction.h"
#include "mainMenu.h"

void initPeripherals(){

// ports
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Debug mode is ON");
#else
  pinMode(fanEnablePin, OUTPUT);  digitalWrite(fanEnablePin, LOW);
  pinMode(safeSignPin, OUTPUT);   digitalWrite(safeSignPin, LOW);
#endif
  pinMode(generatorPin, OUTPUT);  digitalWrite(generatorPin, LOW);
  pinMode(decomposerPin, OUTPUT); digitalWrite(decomposerPin, LOW);
  pinMode(humidifierPin, OUTPUT); digitalWrite(humidifierPin, LOW);
  pinMode(lcdBrightPin, OUTPUT);

  // display
  lcdBrightness = config.brightness();
  LCD = new LiquidCrystal(lcdResetPin, lcdEnablePin, lcdData4Pin, lcdData5Pin, lcdData6Pin, lcdData7Pin);
  LCD->begin(16,2);
  LCD->clear();
  analogWrite(lcdBrightPin, lcdBrightness);

  // humidity sensor
  Wire.begin();
  if (humiditySensor.Read()>0) {
    humiditySensorPresent = false;
  }
  else {
    humiditySensorPresent = true;
  }

}

void setup()
{
  initPeripherals();
  initMenus();
}

void loop()
{
  int buttonState = read_LCD_buttons();
  if (buttonState != lastButton)
  {
    activeMenu->getLCD()->setCursor(0,0);
    switch (buttonState)
    {
    case btnDOWN :
      activeMenu->getLCD()->print(activeMenu->next()->getName());
      break;
    case btnUP :
      activeMenu->getLCD()->print(activeMenu->prev()->getName());
      break;
    case btnRIGHT :
      delay(100);
      activeMenu->selectOption();
	  break;
	case btnLEFT :
	  if (activeMenu->hasParentMenu()) {
#ifdef DEBUG
	      Serial.println("Setting parentMenu as activeMenu");
#endif
		  activeMenu = activeMenu->getParentMenu();
	  }
	  break;
    case btnTIMER :
      timerAction();
      break;
    }
    if (buttonState != btnNONE) activeMenu->display();
    lastButton = buttonState;
  }
}
