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
  }
  else {
    mainMenu->getLCD()->clear();
    mainMenu->getLCD()->setCursor(0,0);
    mainMenu->getLCD()->print("No sensor.");
  }
  holdUntilEscape();
}
