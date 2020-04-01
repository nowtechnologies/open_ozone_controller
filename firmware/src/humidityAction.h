void humidityAction()
{
  if (humiditySensorPresent)
  {
    mainMenu->getLCD()->clear();
    mainMenu->getLCD()->setCursor(0,0);
    mainMenu->getLCD()->print("Humidity / Temp.");
    mainMenu->getLCD()->setCursor(0,1);
    mainMenu->getLCD()->print(humiditySensor.Humidity);
    mainMenu->getLCD()->print("/");
    mainMenu->getLCD()->print(humiditySensor.cTemp);
#ifdef DEBUG
	Serial.println("Humidity / Temp.");
	Serial.print(humiditySensor.Humidity);
	Serial.print("/");
	Serial.print(humiditySensor.cTemp);
#endif
  }
  else {
    mainMenu->getLCD()->clear();
    mainMenu->getLCD()->setCursor(0,0);
    mainMenu->getLCD()->print("No sensor.");
#ifdef DEBUG
	Serial.println("No sensor.");
#endif
  }
  holdUntilEscape();
}
