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
