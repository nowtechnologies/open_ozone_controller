#ifndef _CONTROLLER_MAIN_MENU_HEADER_
#define _CONTROLLER_MAIN_MENU_HEADER_

void nada() {
}

void settingsAction() {
  activeMenu = settingsMenu;
}

void testAction() {
  activeMenu = testMenu;
}

void initMenus(){

  // Main menu
  mainMenu = new LCDMenu(F("Main Menu"), LCD);
  LCDMenuItem *newItem;

  newItem = new LCDMenuItem(F("START !"));
  newItem->setAction(&processAction);
  mainMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem(F("Configure"));
  newItem->setAction(&settingsAction);
  mainMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem(F("Ozone level"));
  newItem->setAction(&ozoneDisplayAction);
  mainMenu->addMenuItem(newItem);

  // newItem = new LCDMenuItem("Humidity level");
  // newItem->setAction(&humidityAction);
  // mainMenu->addMenuItem(newItem);

  // newItem = new LCDMenuItem("Set timer");
  // newItem->setAction(&timerAction);
  // mainMenu->addMenuItem(newItem);

  // Settings Menu, whose parent menu is mainMenu
  settingsMenu = new LCDMenu(F("Settings Menu"), LCD, mainMenu);

  newItem = new LCDMenuItem(F("Set Decon Time"));
  newItem->setAction(&deconTimeAction);
  settingsMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem(F("Set Kill Level"));
  newItem->setAction(&killLevelAction);
  settingsMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem(F("Set threshold"));
  newItem->setAction(&controlThresholdAction);
  settingsMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem(F("Set Lock"));
  newItem->setAction(&lockInstalledAction);
  settingsMenu->addMenuItem(newItem);

  // newItem = new LCDMenuItem("Calibrate O3");
  // newItem->setAction(&ozoneCalibrationAction);
  // settingsMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem(F("Set brightness"));
  newItem->setAction(&brightnessAction);
  settingsMenu->addMenuItem(newItem);

  newItem = new LCDMenuItem(F("Firmware info"));
  newItem->setAction(&firmwareInfoAction);
  settingsMenu->addMenuItem(newItem);

	// Test actuators
  newItem = new LCDMenuItem(F("Test outputs"));
	newItem->setAction(&testAction);
	mainMenu->addMenuItem(newItem);

	testMenu = new LCDMenu(F("Test Menu"), LCD, mainMenu);

	newItem = new LCDMenuItem(F("Test generator"));
  newItem->setAction(&generatorTestAction);
  testMenu->addMenuItem(newItem);

	newItem = new LCDMenuItem(F("Test blower"));
	newItem->setAction(&blowerTestAction);
	testMenu->addMenuItem(newItem);

	newItem = new LCDMenuItem(F("Test decomposer"));
	newItem->setAction(&decomposerTestAction);
	testMenu->addMenuItem(newItem);

	newItem = new LCDMenuItem(F("Test humidifier"));
  newItem->setAction(&humidifierTestAction);
  testMenu->addMenuItem(newItem);

	newItem = new LCDMenuItem(F("Test lock"));
  newItem->setAction(&lockTestAction);
  testMenu->addMenuItem(newItem);

  // displayPOST();
  // Set the mainMenu as active
  activeMenu = mainMenu;
  activeMenu->display();
}

#endif
