#ifndef _CONTROLLER_PROCESS_ACTION_HEADER_H_
#define _CONTROLLER_PROCESS_ACTION_HEADER_H_

Timer restTimer;

void processAction()
{
  int buttonState = btnNONE;

  // check wheter we can start the process
  if (ozoneMonitorConnected && int(sensorPacket.temperature)==0)
  {
    displayWarning(F("Sensor Failure"));
    holdUntilEscape();
  }
  else if (!ozoneMonitorConnected && !SPIozoneSensorPresent)
  {
    displayWarning(F("No sensors"));
    holdUntilEscape();
  }
  // if there is an ozone sensor ask for confirmation
  else
  {
    displayInfo(F("Start process?"),F("No   Yes"));
    delay(200);
    if (waitForButtonPress() == btnRIGHT){ // yes !!!

      // LOCKING DOOR
      if (lockInstalled){
        displayInfo(F("Locking door..."));
        portEnabled[lock]=true;
        delay(2000); // e.g.
        updatePorts();
      }

      // clear port states and disable all peripherals
      shutDownPeripherals();

      // FLOODING CHAMBER WITH OZONE GAS
      displayInfo(F("Flooding chamber"),F("with ozone..."));
      portEnabled[blower] = true; // turn fan ON
      updatePorts();
      delay(2000); // wait for the user to read the message
      uint32_t milliseconds = deconTime*60000; // minutes to millis
      timer.set(milliseconds);
      bool genAllowed = true; // allow generator to be turned on

      while ( buttonState != btnLEFT ) // do until user escape or timer break
      {
        buttonState = read_LCD_buttons();

        if (ozoneMonitorConnected) checkIncomingSerial(); // check for new packets
        if (ozoneLevel() > killLevel + ctrlThreshold)
        {
          portEnabled[generator] = false;
          updatePorts();
        }
        if ((ozoneLevel() < killLevel - ctrlThreshold) && genAllowed)
        {
          portEnabled[generator] = true;
          updatePorts();
          delay(generatorPulseLength()/5); // short generator burst
          portEnabled[generator] = false; //  forbid further generation
          updatePorts();
          restTimer.set(generatorPulseLength()*5); // wait for the sensor
          genAllowed = false;
        }

        if (restTimer.poll()) genAllowed = true; // re-allow generation
        if (timer.poll()) break; // time is up, exit the ozone loop
        uint32_t secondsRemaining = round(timer.TimeRemaining()/1000);
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
      }

      // DECONTAMINATION
      buttonState = btnNONE; // clear button state
      displayInfo(F("O3 destruction"),F("in progress..."));
      portEnabled[generator]  = false; // disable generation
      portEnabled[decomposer] = true;  // enable destruction
      updatePorts();
      delay(2000);
      while ( buttonState != btnLEFT )
      {
        buttonState = read_LCD_buttons();
        if (ozoneMonitorConnected) checkIncomingSerial();
        if (millis()%1000==0)
        {
          mainMenu->getLCD()->clear();
          mainMenu->getLCD()->setCursor(0,0);
          mainMenu->getLCD()->print(F("O3 destruction"));
          mainMenu->getLCD()->setCursor(0,1);
          mainMenu->getLCD()->print(F("PPM: "));
          mainMenu->getLCD()->print(ozoneLevel());
        }
        if (ozoneLevel()<=9.0) break; // <-- WARNING: THIS SHOULD BE 3.0 !!!
        // IN ORDER TO MAKE THIS SAFE, WE NEED A MORE PRECISE SENSOR
      }
      portEnabled[decomposer] = false;
      portEnabled[blower]     = false;
      updatePorts(); // turn off everything

      // OPENING DOOR
      if (lockInstalled){
        displayInfo(F("Opening door..."));
        portEnabled[lock] = false;
        delay(2000);
        updatePorts();
      }

    } // eof selected yes
    else { } // user said no, nothing to do
  } // eof no error
}// eof process

#endif
