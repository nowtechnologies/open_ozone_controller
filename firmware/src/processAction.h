#ifndef _CONTROLLER_PROCESS_ACTION_HEADER_H_
#define _CONTROLLER_PROCESS_ACTION_HEADER_H_

void updatePorts()
{
  for (uint8_t p=0; p<5; p++){
    digitalWrite(portPin[p], portEnabled[p]);
  }
}

uint32_t generatorPulseLength()
{
  float volume = chamberVolume/1000.0f; // m^3
  float concentration = killLevel/467.0f; // g/m^3
  float requiredMass  = concentration*volume; // g
  float productPerSec = generatorCapacity/3600; // g/s
  return round((requiredMass/productPerSec)*1000); // millis
}

void processAction()
{
  int buttonState = btnNONE;

  if (ozoneMonitorConnected && int(sensorPacket.temperature)==0)
  {
    mainMenu->getLCD()->clear();
    mainMenu->getLCD()->setCursor(0,0);
    mainMenu->getLCD()->print(F("WARNING!"));
    mainMenu->getLCD()->setCursor(0,1);
    mainMenu->getLCD()->print(F("Sensor Failure"));
    holdUntilEscape();
  }
  else if (!ozoneMonitorConnected && !SPIozoneSensorPresent)
  {
    mainMenu->getLCD()->clear();
    mainMenu->getLCD()->setCursor(0,0);
    mainMenu->getLCD()->print(F("WARNING!"));
    mainMenu->getLCD()->setCursor(0,1);
    mainMenu->getLCD()->print(F("No sensors"));
    holdUntilEscape();
  }
  else
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
        delay(2000); // e.g.
        updatePorts();
      }

      // FLOODING CHAMBER WITH OZONE GAS
      mainMenu->getLCD()->clear();
      mainMenu->getLCD()->setCursor(0,0);
      mainMenu->getLCD()->print(F("Flooding chamber"));
      mainMenu->getLCD()->setCursor(0,1);
      mainMenu->getLCD()->print(F("with ozone..."));
      portEnabled[blower] = true;
      updatePorts();
      delay(2000);
      uint32_t milliseconds = deconTime*60000;
      timer.set(milliseconds);

      while ( buttonState != btnLEFT )
      {
        buttonState = read_LCD_buttons();

        if (ozoneMonitorConnected) checkIncomingSerial(); // check for new packets
        if (ozoneLevel() > killLevel + ctrlThreshold)
        {
          portEnabled[generator] = false;
          updatePorts();
        }
        if (ozoneLevel() < killLevel - ctrlThreshold)
        {
          // turn generator on for a fraction of required time
          portEnabled[generator] = true;
          updatePorts();
          delay(generatorPulseLength()/10); // 1/10 ?
          portEnabled[generator] = false;
          updatePorts();
          delay(1000);
        }

        if (timer.poll()) break;
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
      mainMenu->getLCD()->clear();
      mainMenu->getLCD()->setCursor(0,0);
      mainMenu->getLCD()->print(F("O3 destruction"));
      mainMenu->getLCD()->setCursor(0,1);
      mainMenu->getLCD()->print(F("in progress..."));
      portEnabled[generator]  = false;
      portEnabled[decomposer] = true;
      updatePorts();
      while ( buttonState != btnLEFT )
      {
        buttonState = read_LCD_buttons();
        if (ozoneLevel()<=1.0) break; // !!! needs a low concentration sensor
      }
      portEnabled[decomposer] = false;
      portEnabled[blower]     = false;

      // OPENING DOOR
      if (lockInstalled){
        mainMenu->getLCD()->clear();
        mainMenu->getLCD()->setCursor(0,0);
        mainMenu->getLCD()->print(F("Opening door..."));
        portEnabled[lock] = false;
        delay(2000);
        updatePorts();
      }

    } // eof selected yes
    else { } // user said no, nothing to do
  } // eof no error
}// eof process

#endif
