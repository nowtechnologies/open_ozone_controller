void firmwareInfoAction()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print(F("Firmware version:"));
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(fw_major);
  mainMenu->getLCD()->print(F("."));
  mainMenu->getLCD()->print(fw_minor);
  mainMenu->getLCD()->print(F("."));
  mainMenu->getLCD()->print(fw_fix);
  holdUntilEscape();
}
