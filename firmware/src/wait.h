#ifndef _CONTROLLER_WAIT_FUNCTION_H_
#define _CONTROLLER_WAIT_FUNCTION_H_

void wait(uint32_t millis){
  timer.set(millis);
  while (!timer.poll()){
    statusReport();
  }
}

#endif
