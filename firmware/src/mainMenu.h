#ifndef _CONTROLLER_MAIN_MENU_HEADER_
#define _CONTROLLER_MAIN_MENU_HEADER_

void nada() {
#ifdef DEBUG
	Serial.println("This feature is not available yet");
#endif
}

void settingsAction() {
  activeMenu = settingsMenu;
}

void testAction() {
  activeMenu = testMenu;
}

void initMenus(){

  // Main menu
  mainMenu = new LCDMenu("Main Menu", LCD);
  LCDMenuItem *newItem;

  newItem = new LCDMenuItem("Start");
  newItem->setAction(&processAction);
  mainMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem("Ozone level");
  newItem->setAction(&nada);
  mainMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem("Humidity level");
  newItem->setAction(&humidityAction);
  mainMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem("Set timer");
  newItem->setAction(&timerAction);
  mainMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem("Settings");
  newItem->setAction(&settingsAction);
  mainMenu->addMenuItem(newItem);

	newItem = new LCDMenuItem("Test periphery");
	newItem->setAction(&testAction);
	mainMenu->addMenuItem(newItem);

  // Settings Menu, whose parent menu is mainMenu
  settingsMenu = new LCDMenu("Settings Menu", LCD, mainMenu);

  newItem = new LCDMenuItem("Set brightness");
  newItem->setAction(&brightnessAction);
  settingsMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem("Firmware info");
  newItem->setAction(&firmwareInfoAction);
  settingsMenu->addMenuItem(newItem);

	// Test actuators
	testMenu = new LCDMenu("Test Menu", LCD, mainMenu);

	newItem = new LCDMenuItem("Test generator");
  newItem->setAction(&generatorTestAction);
  testMenu->addMenuItem(newItem);

	newItem = new LCDMenuItem("Test blower");
	newItem->setAction(&blowerTestAction);
	testMenu->addMenuItem(newItem);

	newItem = new LCDMenuItem("Test humidifier");
  newItem->setAction(&humidifierTestAction);
  testMenu->addMenuItem(newItem);

	newItem = new LCDMenuItem("Test decomposer");
  newItem->setAction(&decomposerTestAction);
  testMenu->addMenuItem(newItem);

  // Set the mainMenu as active
  activeMenu = mainMenu;

  displayPOST();
  activeMenu->display();
}

#endif
