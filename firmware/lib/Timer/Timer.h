#ifndef __TIMER_H__
#define __TIMER_H__

#include "Arduino.h"

class Timer final {
private:
  static constexpr uint32_t cMaxDelay = 1ul << 31ul;

  uint32_t mExpireTimepoint = 0;
  bool mRunning = false;

public:
  void set(uint32_t aDelay) noexcept {
    mRunning = true;
    mExpireTimepoint = millis() + aDelay;
  }

  bool poll() noexcept;
  uint32_t TimeRemaining();
};

void delay(uint16_t aDelay, volatile bool *aInterrupt);

#endif
