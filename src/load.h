#ifndef load_h
#define load_h

#include "Arduino.h"

namespace toggles {
  const bool test = 1; //may cause issue with modulo based timing
}

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
  const int ST_OUT_THEO_UPPER = 180;//theoretical upper limits of throttle/steer input
  const int ST_OUT_THEO_LOWER = 0;
  static int ST_OUT_UPPER = 180;//constant style caps from old version
  static int ST_OUT_LOWER = 0;

  const int TH_OUT_THEO_UPPER = 780; //theoretical upper limits of throttle/steer input
  const int TH_OUT_THEO_LOWER = 0;
  static int TH_OUT_UPPER = 780;//constant style caps from old version
  static int TH_OUT_LOWER = 0;

  const int TH_IN_UPPER = 802;
  const int TH_IN_LOWER = 272;
  static int TH_DEADZONE = 30;//stored on analog side (1/1024)ths

  static bool stInvert;
  const int ST_IN_UPPER = 930;
  const int ST_IN_LOWER = 28;
  static int ST_DEADZONE = 20; //stored on analog side (1/1024)ths
}

#endif
