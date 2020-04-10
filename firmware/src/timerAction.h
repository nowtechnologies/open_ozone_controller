uint32_t lastTime = 0;

void timerAction(){
  int buttonState = btnNONE;
  uint16_t timerSeconds = 10;
  boolean timerStarted  = false;
  displayTopic(F("Start timer: "));
  displayValue(timerSeconds,F("sec"));
  shutDownPeripherals();

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
            displayTopic(F("Time left:"));
            portEnabled[generator] = true;
            portEnabled[blower] = true;
            updatePorts();
        break;
        }
        lastButton = buttonState;
        displayValue(timerSeconds,F("sec"));
      }

      if (timerStarted)
      {
        uint32_t remaining = round(timer.TimeRemaining()/1000);
        if (!timer.poll() && lastTime != remaining)
        {
          displayValue(remaining,F("sec"));
          lastTime = remaining;
        }
        if (timer.poll()) {
          portEnabled[generator] = false;
          portEnabled[blower] = false;
          updatePorts();
          break;
        }
      }

  }
  shutDownPeripherals(); // just to be on the safe side
}
