#ifndef _CONTROLLER_PROCESS_ACTION_HEADER_H_
#define _CONTROLLER_PROCESS_ACTION_HEADER_H_

Timer restTimer;

void updatePorts()
{
  for (uint8_t p=0; p<5; p++){
    digitalWrite(portPin[p], portEnabled[p]);
  }
}

uint32_t generatorPulseLength()
{
  float concentration = killLevel/467.0f; // g/m^3 def: 0.05
  float requiredMass  = concentration*chamberVolume; // mg def: 5
  float productPerSec = generatorCapacity/3600; // mg/s def: 1.38
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

      for (uint8_t p=0; p<5; p++){
        portEnabled[p]=false;
      }
      updatePorts();

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
      bool genAllowed = true;

      while ( buttonState != btnLEFT )
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
      buttonState = btnNONE;
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
        if (ozoneLevel()<=9.0) break; // !!! needs a low concentration sensor
      }
      portEnabled[decomposer] = false;
      portEnabled[blower]     = false;
      updatePorts();

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
