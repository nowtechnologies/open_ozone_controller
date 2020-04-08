#ifndef _CONTROLLER_PROCESS_ACTION_HEADER_H_
#define _CONTROLLER_PROCESS_ACTION_HEADER_H_

/*

1. sure? -> lock on
2. gen-on, blow-on, timer start
3. level control until times up
4. times up -> gen-off, uvc-on
5. wait for low ppm -> lock off

e.g.:
while (control) {
 o3 = sensor.read();
 if (o3 > target + threshold) gen.off();
 if (o3 < target - threshold) gen.on();
}

*/

void updatePorts()
{
  for (uint8_t p=0; p<5; p++){
    digitalWrite(portPin[p], portEnabled[p]);
  }
}

void processAction()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print(F("Start process?"));
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print(F("No   Yes"));
  delay(200);

  if (waitForButtonPress() == btnRIGHT){ // yes

    // LOCKING DOOR
    if (lockInstalled){
      mainMenu->getLCD()->clear();
      mainMenu->getLCD()->setCursor(0,0);
      mainMenu->getLCD()->print(F("Locking door..."));
      portEnabled[lock]=true;
      delay(1000); // e.g.
      updatePorts();
    }

    // FLOODING CHAMBER WITH OZONE GAS
    mainMenu->getLCD()->clear();
    mainMenu->getLCD()->setCursor(0,0);
    mainMenu->getLCD()->print(F("Ozone flood:"));
    timer.set(deconTime*60*1000); // decontamination time is in minutes
    int buttonState = btnNONE;
    while ( !timer.poll() || buttonState != btnLEFT ){ // until time's up or canceled
      buttonState = read_LCD_buttons();
      uint32_t secondsRemaining = round(timer.TimeRemaining()/1000);
      if (lastTime != secondsRemaining)
      {
        clearSecondLcdRow();
        mainMenu->getLCD()->print(secondsRemaining);
        mainMenu->getLCD()->print(F(" sec"));
        lastTime = secondsRemaining;
      }
    }

    // DECONTAMINATION

  }
  else { } // user said no, nothing to do
}

#endif
