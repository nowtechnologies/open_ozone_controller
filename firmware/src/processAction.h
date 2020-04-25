#ifndef _CONTROLLER_PROCESS_ACTION_HEADER_H_
#define _CONTROLLER_PROCESS_ACTION_HEADER_H_

Timer processTimer;
Timer restTimer;

void processAction()
{
  int buttonState = btnNONE;

  // check wheter we can start the process
  if (!ozoneMonitorConnected)
  {
    displayWarning(F("No Sensor"));
    holdUntilEscape();
  }
  // if there is an ozone sensor ask for confirmation
  else
  {
    displayInfo(F("Start process?"),F("No   Yes"));
    wait(200);
    if (waitForButtonPress() == btnRIGHT){ // yes !!!

      // clear port states and disable all peripherals
      shutDownPeripherals();

      // LOCKING DOOR
      if (lockInstalled){
        displayInfo(F("Locking door..."));
        portEnabled[lock]=true;
        wait(2000); // e.g.
        updatePorts();
      }

      // FLOODING CHAMBER WITH OZONE GAS
      displayInfo(F("Flooding chamber"),F("with ozone..."));
      portEnabled[blower] = true; // turn fan ON
      updatePorts();
      wait(2000); // wait for the user to read the message
      uint32_t milliseconds = deconTime*60000; // minutes to millis
      processTimer.set(milliseconds);
      bool genAllowed = true; // allow generator to be turned on

      while ( buttonState != btnLEFT ) // do until user escape or timer break
      {
        buttonState = read_LCD_buttons();

        checkIncomingSerial(); // check for new packets
        if (ozoneLevel() > killLevel + ctrlThreshold)
        {
          portEnabled[generator] = false;
          updatePorts();
        }
        if ((ozoneLevel() < killLevel - ctrlThreshold) && genAllowed)
        {
          portEnabled[generator] = true;
          updatePorts();
          // WARNING: some power supplies have a minimum up-time
          delay(generatorPulseLength()/10); // short generator burst
          portEnabled[generator] = false; //  forbid further generation
          updatePorts();
          // WARNING: time multiplier should depend on fan capacity
          restTimer.set(generatorRestTime*1000); // wait for the sensor
          genAllowed = false;
        }

        if (restTimer.poll()) genAllowed = true; // re-allow generation
        if (processTimer.poll()) break; // time is up, exit the ozone loop
        uint32_t secondsRemaining = round(processTimer.TimeRemaining()/1000);
        if (lastTime != secondsRemaining)
        {
          mainMenu->getLCD()->clear();
          mainMenu->getLCD()->setCursor(0,0);
          mainMenu->getLCD()->print(F("PPM: "));
          mainMenu->getLCD()->print(ozoneLevel());
          mainMenu->getLCD()->setCursor(0,1);
          mainMenu->getLCD()->print(F("SEC: "));
          mainMenu->getLCD()->print(secondsRemaining);
          lastTime = secondsRemaining;
        }
        statusReport();
      }

      // DECONTAMINATION
      buttonState = btnNONE; // clear button state
      portEnabled[generator]  = false; // disable generation
      portEnabled[decomposer] = true;  // enable destruction
      updatePorts();
      displayInfo(F("O3 destruction"),F("in progress..."));
      wait(2000);
      while ( buttonState != btnLEFT )
      {
        buttonState = read_LCD_buttons();
        checkIncomingSerial();
        if (millis()%1000==0)
        {
          mainMenu->getLCD()->clear();
          mainMenu->getLCD()->setCursor(0,0);
          mainMenu->getLCD()->print(F("O3 destruction"));
          mainMenu->getLCD()->setCursor(0,1);
          mainMenu->getLCD()->print(F("PPM: "));
          mainMenu->getLCD()->print(ozoneLevel());
        }
        if (ozoneLevel()<=3.0) break; // MAC 3.0 ppm for 15 mins
        // IN ORDER TO MAKE THIS SAFE, WE NEED A MORE PRECISE SENSOR
        statusReport();
      }
      portEnabled[decomposer] = false;
      portEnabled[blower]     = false;
      updatePorts(); // turn off everything

      // OPENING DOOR
      if (lockInstalled){
        displayInfo(F("Opening door..."));
        portEnabled[lock] = false;
        wait(2000);
        updatePorts();
      }

    } // eof selected yes
    else { // user said no
      shutDownPeripherals();
    }
  } // eof no error
}// eof process

#endif
