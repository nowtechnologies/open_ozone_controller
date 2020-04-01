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
#ifdef DEBUG
  Serial.println("Firmware version:");
  Serial.print(fw_major);
  Serial.print(".");
  Serial.print(fw_minor);
  Serial.print(".");
  Serial.println(fw_fix);
#endif
  holdUntilEscape();
}
