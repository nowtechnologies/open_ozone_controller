// Libraries
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <LCDMenu.h>
#include <LCDMenuItem.h>
#include <Storage.h>
#include <Timer.h>

// hard coded definitions
#include "version.h"
#include "pinMap.h"
#include "packets.h"

// Globals
bool ozoneMonitorConnected    = false;
UARTHEADER packetHeader;
SENSORPACK sensorPacket;
GPIOS      internal;
LOG        logData;
LiquidCrystal* LCD;
LCDMenu* activeMenu;
LCDMenu* mainMenu;
LCDMenu* settingsMenu;
LCDMenu* testMenu;
Storage  config;
Timer    timer;

enum peripherals{
  generator,
  blower,
  decomposer,
  humidifier,
  lock
};

String  nameOfPeripherals[] = {"Generator","Blower","Decomposer","Humidifier","Lock"};
uint8_t portPin[] = {generatorPin, fanEnablePin, decomposerPin, humidifierPin, safeSignPin};
bool    portEnabled[] = {false, false, false, false, false};

// Stored variables
uint8_t  deconTime;
uint8_t  killLevel;
uint8_t  lcdBrightness;
uint8_t  ctrlThreshold;
uint8_t  generatorRestTime;
bool     lockInstalled;
bool     LogEnabled;
uint16_t generatorCapacity;
uint16_t chamberVolume;

// Lazy de-spaghetti headers
#include "uartcomm.h"
#include "wait.h"
#include "peripherals.h"
#include "buttonUtils.h"
#include "displayUtils.h"
#include "fwInfoAction.h"
#include "humidityAction.h"
#include "settingsAction.h"
#include "testAction.h"
#include "ozoneAction.h"
#include "timerAction.h"
#include "processAction.h"
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
  // Config
  config.begin();
  deconTime = config.deconTime();
  killLevel = config.killLevel();
  ctrlThreshold = config.controlThreshold();
  lockInstalled = config.lockInstalled();
  LogEnabled   = config.serialLogEnabled();
  chamberVolume = config.chamberVolume();
  generatorCapacity = config.generatorCapacity();
  generatorRestTime = config.restTime();
  // Display
  lcdBrightness = config.brightness();
  LCD = new LiquidCrystal(lcdResetPin, lcdEnablePin, lcdData4Pin, lcdData5Pin, lcdData6Pin, lcdData7Pin);
  LCD->begin(16,2);
  LCD->clear();
  analogWrite(lcdBrightPin, lcdBrightness);
  initMenus();
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
  statusReport();
}
