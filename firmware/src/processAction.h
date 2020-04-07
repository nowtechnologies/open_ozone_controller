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

void updatePorts(){
  for (uint8_t p=0; p<5; p++){
    digitalWrite(portPin[p], portEnabled[p]);
  }
}

void processAction()
{
  mainMenu->getLCD()->clear();
  mainMenu->getLCD()->setCursor(0,0);
  mainMenu->getLCD()->print("Start process?");
  mainMenu->getLCD()->setCursor(0,1);
  mainMenu->getLCD()->print("No   Yes");
  delay(200);
  if (waitForButtonPress() == btnRIGHT){ // yes

    if (lockInstalled){
      mainMenu->getLCD()->clear();
      mainMenu->getLCD()->setCursor(0,0);
      mainMenu->getLCD()->print("Locking door...");
      portEnabled[lock]=true;
      delay(1000); // e.g.
      updatePorts();
    }

    holdUntilEscape(); // temporary
  } else {
    // user said no, nothing to do
  }
}

#endif
