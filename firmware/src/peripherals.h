#ifndef _CONTROLLER_PERIPHERAL_UTILS_H_
#define _CONTROLLER_PERIPHERAL_UTILS_H_

void updatePorts()
{
  for (uint8_t p=0; p<5; p++){
    digitalWrite(portPin[p], portEnabled[p]);
  }
}

void shutDownPeripherals(){
  for (uint8_t p=0; p<5; p++){
    portEnabled[p]=false;
  }
  updatePorts();
}

uint32_t generatorPulseLength()
{
  float concentration = killLevel/467.0f; // g/m^3 def: 0.05
  float requiredMass  = concentration*chamberVolume; // mg def: 5
  float productPerSec = generatorCapacity/3600; // mg/s def: 1.38
  return round((requiredMass/productPerSec)*1000); // millis
}

#endif
