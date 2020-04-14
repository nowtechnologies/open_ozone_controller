uint32_t lastTime = 0;

void timerAction(){
  int buttonState = btnNONE;
  uint16_t timedMillis = 0;
  boolean timerStarted  = false;
  displayTopic(F("Start timer: "));
  displayValue(timedMillis,F("ms"));
  portEnabled[generator]  = false;
  portEnabled[decomposer] = false;
  portEnabled[blower]     = true;
  updatePorts();

  while (buttonState != btnLEFT) {

      buttonState = read_LCD_buttons();
      if (buttonState != lastButton && !timerStarted)
      {
        switch (buttonState)
        {
        case btnDOWN :
            timedMillis-=100;
            if (timedMillis < 0) timedMillis = 0;
        break;
        case btnUP :
            timedMillis+=100;
            if (timedMillis > 65500) timedMillis = 65500;
        break;
        case btnRIGHT :
            timer.set(timedMillis);
            timerStarted = true;
            displayTopic(F("Time left:"));
            portEnabled[generator] = true;
            portEnabled[blower]    = true;
            updatePorts();
        break;
        }
        lastButton = buttonState;
        displayValue(timedMillis,F("ms"));
      }

      if (timerStarted)
      {
        if (millis()%100==0)
        {
          displayValue(timer.TimeRemaining(),F("ms"));
        }
        if (timer.poll()) {
          portEnabled[generator] = false;
          updatePorts();
          break;
        }
      }

  }
}
