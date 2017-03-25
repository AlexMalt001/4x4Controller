#include <Adafruit_ILI9341.h>

#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include <TouchScreen.h>

#include "serialProcess.h"
#include "screen.h"
#include "load.h"

int th;
int st;

const int PWM_UPPER = 200;
const int PWM_LOWER = 100;

const int TH_UPPER = 799;
const int TH_LOWER = 278;
const int TH_DEADZONE = 30;

const int ST_UPPER = 950;
const int ST_LOWER = 0;
const int ST_DEADZONE = 20;

pins pins;
serialProcess io;
dataProcess data;

void setup() {
  load::modeSet();
  load::serialSetup();
}

void loop() {

}
