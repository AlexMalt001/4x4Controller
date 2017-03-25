#include <Adafruit_ILI9341.h>

#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include <TouchScreen.h>

#include "serialProcess.h"
#include "screen.h"
#include "load.h"

serialProcess io;
dataProcess data;

using namespace pins;
using namespace varStore;

int ldrValue;
bool tiltValue;

void setup() {
  load::modeSet();
  load::serialSetup();
}

void loop() {
  int thOut = data.processVars(analogRead(throttle),TH_IN_UPPER,
      TH_IN_LOWER, TH_DEADZONE, TH_OUT_UPPER, TH_OUT_LOWER);

  int stOut = data.processVars(analogRead(steer), ST_IN_UPPER,
      ST_IN_LOWER, ST_DEADZONE, ST_OUT_UPPER, ST_OUT_LOWER);

  io.sendVars(thOut, stOut);

  if ((millis() % 50) == 0) {
      int outArray[1];
      //int *p =
    }
}

void serialEvent() {
   while (Serial.available()) {
     tiltValue = Serial.readStringUntil(',').toInt();
     Serial.read();
     ldrValue = Serial.readStringUntil(',').toInt();
     Serial.readStringUntil("/n");
   }
}
