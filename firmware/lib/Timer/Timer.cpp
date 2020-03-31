#include "Arduino.h"
#include "Timer.h"

bool Timer::poll() noexcept {
  if(!mRunning) {
    return true;
  }
  else {
    uint32_t now = millis();
    if(mExpireTimepoint < now) {
      mRunning = now - mExpireTimepoint > cMaxDelay;
    }
    else if(now < mExpireTimepoint) {
      mRunning = mExpireTimepoint - now < cMaxDelay;
    }
    else {
      mRunning = false;
    }
    return !mRunning;
  }
}

uint32_t Timer::TimeRemaining(){
  uint32_t now = millis();
  uint32_t remaining = 0;
  if(mExpireTimepoint < now) {
    remaining = now - mExpireTimepoint;
  }
  else if(now < mExpireTimepoint) {
    remaining = mExpireTimepoint - now;
  }
  return remaining;
}

void delay(uint16_t aDelay, volatile bool *aInterrupt) {
  if(aInterrupt == nullptr) {
    delay(aDelay);
  }
  else {
    while(aDelay > 0) {
      if(*aInterrupt) {
        break;
      }
      --aDelay;
      delay(1);
    }
  }
}
