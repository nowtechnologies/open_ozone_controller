#ifndef _CONTROLLER_MAIN_MENU_HEADER_
#define _CONTROLLER_MAIN_MENU_HEADER_

void nada(){}

void initMainMenu(){
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

  displaySplash();
  mainMenu->display();
}

#endif
