// hard coded definitions
#include "version.h"
#include "pinMap.h"

// Libraries
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <LCDMenu.h>
#include <LCDMenuItem.h>
#include <Storage.h>
#include <Timer.h>
#include <MCP335X.h>
#include <MQ131.h>
#include <uartcomm.h>

// Globals
bool SPIozoneSensorPresent    = false;
bool SPIhumiditySensorPresent = false; // probably going to be a BMP280

MCP335X adc(chipSelect2, spiMOSI, spiMISO, spiSCK);
MQ131   ozoneSensor(MQ131Model::HighConcentration, &adc);
LiquidCrystal* LCD;
LCDMenu* activeMenu;
LCDMenu* mainMenu;
LCDMenu* settingsMenu;
LCDMenu* testMenu;
Storage  config;
Timer    timer;

// Headers
#include "buttonUtils.h"
#include "displayUtils.h"
#include "timerAction.h"
#include "fwInfoAction.h"
#include "humidityAction.h"
#include "brightnessAction.h"
#include "testAction.h"
#include "processAction.h"
#include "ozoneAction.h"
#include "mainMenu.h"

void initPorts()
{
  pinMode(generatorPin,  OUTPUT); digitalWrite(generatorPin,  LOW);
  pinMode(fanEnablePin,  OUTPUT); digitalWrite(fanEnablePin,  LOW);
  pinMode(decomposerPin, OUTPUT); digitalWrite(decomposerPin, LOW);
  pinMode(humidifierPin, OUTPUT); digitalWrite(humidifierPin, LOW);
  pinMode(safeSignPin,   OUTPUT); digitalWrite(safeSignPin,   LOW);
  pinMode(lcdBrightPin,  OUTPUT);
}

void setup()
{
  // Display
  lcdBrightness = config.brightness();
  LCD = new LiquidCrystal(lcdResetPin, lcdEnablePin, lcdData4Pin, lcdData5Pin, lcdData6Pin, lcdData7Pin);
  LCD->begin(16,2);
  LCD->clear();
  analogWrite(lcdBrightPin, lcdBrightness);
  initMenus();
  // SPI ozone sensor
  adc.begin();
  if (adc.isConnected()){
    ozoneSensor.begin();
    ozoneSensor.calibrate();
    SPIozoneSensorPresent = true;
  }
  else {
    SPIozoneSensorPresent = false;
  }
  // GPIO
  initPorts();
  // UART
  Serial.begin(9600);
}

void loop()
{
  checkIncomingSerial();
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
      // delay(100);
      activeMenu->selectOption();
	  break;
	  case btnLEFT :
  	  if (activeMenu->hasParentMenu()) {
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
