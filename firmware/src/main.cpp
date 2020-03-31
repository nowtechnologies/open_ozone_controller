// Libraries
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <LCDMenu.h>
#include <LCDMenuItem.h>
#include <Storage.h>
#include <Timer.h>

LiquidCrystal* LCD;
LCDMenu* mainMenu;
Storage config;
Timer   timer;

// Headers
#include "version.h"
#include "pinMap.h"
#include "buttonUtils.h"
#include "displayUtils.h"
#include "timerAction.h"
#include "fwInfoAction.h"
#include "brightnessAction.h"
#include "generatorAction.h"
#include "processAction.h"

void nada(){}

void setup()
{
  pinMode(fanEnablePin, OUTPUT);  digitalWrite(fanEnablePin, LOW);
  pinMode(safeSignPin, OUTPUT);   digitalWrite(safeSignPin, LOW);
  pinMode(generatorPin, OUTPUT);  digitalWrite(generatorPin, LOW);
  pinMode(decomposerPin, OUTPUT); digitalWrite(decomposerPin, LOW);
  pinMode(humidifierPin, OUTPUT); digitalWrite(humidifierPin, LOW);

  LCD = new LiquidCrystal(lcdResetPin, lcdEnablePin, lcdData4Pin, lcdData5Pin, lcdData6Pin, lcdData7Pin);
  LCD->begin(16,2);
  LCD->clear();

  mainMenu     = new LCDMenu("Main Menu", LCD);
  LCDMenuItem *newItem;

  newItem = new LCDMenuItem("Start");
  newItem->setAction(&processAction);
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

  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("Open Ozone");
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print("Project");
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
      delay(100);
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
