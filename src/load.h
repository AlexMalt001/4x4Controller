#ifndef load_h
#define load_h

#include "Arduino.h"

namespace load {
    void modeSet();
    void serialSetup();
}

namespace pins {

  const int throttle = A0;
  const int steer = A1;
  const int thTrim = A3;
  const int stTrim = A4;
  const int stDR = A7;

  const int thSwitch = 22;
  const int stSwitch = 23;

  const int ledR = 24;
  const int ledG = 25;
};

namespace varStore {
  const int ST_OUT_UPPER = 200;
  const int ST_OUT_LOWER = 100;

  const int TH_OUT_UPPER = 200;
  const int TH_OUT_LOWER = 100;

  const int TH_IN_UPPER = 799;
  const int TH_IN_LOWER = 278;
  const int TH_DEADZONE = 30;

  static bool stInvert;
  const int ST_IN_UPPER = 180;
  const int ST_IN_LOWER = 0;
  const int ST_DEADZONE = 20; //stored on analog side (1/1024)ths
}

#endif
