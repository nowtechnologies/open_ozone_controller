uint32_t lastTime = 0;

void timerAction(){
  int buttonState = btnNONE;
  uint16_t timerSeconds = 10;
  boolean timerStarted = false;
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("Start timer: ");
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(timerSeconds);
  mainMenu->getLCD()->print(" sec");

  while (buttonState != btnLEFT) {

      buttonState = read_LCD_buttons();
      if (buttonState != lastButton && !timerStarted)
      {
        switch (buttonState)
        {
        case btnDOWN :
            timerSeconds--;
            if (timerSeconds < 0) timerSeconds = 0;
        break;
        case btnUP :
            timerSeconds++;
            if (timerSeconds > 65535) timerSeconds = 65535;
        break;
        case btnRIGHT :
            timer.set(timerSeconds*1000);
            timerStarted = true;
            mainMenu->getLCD()->clear();
            mainMenu->getLCD()->setCursor(0,0);
            mainMenu->getLCD()->print("Time left: ");

            digitalWrite(generatorPin, HIGH);
        break;
        }
        lastButton = buttonState;
        clearSecondLcdRow();
        mainMenu->getLCD()->print(timerSeconds);
        mainMenu->getLCD()->print(" sec");
      }

      if (timerStarted)
      {
        uint32_t remaining = round(timer.TimeRemaining()/1000);
        if (!timer.poll() && lastTime != remaining)
        {
          clearSecondLcdRow();
          mainMenu->getLCD()->print(remaining);
          mainMenu->getLCD()->print(" sec");
          lastTime = remaining;
        }
        if (timer.poll()) {
          digitalWrite(generatorPin, LOW);
        }
      }

  }
  digitalWrite(generatorPin, LOW);
}
