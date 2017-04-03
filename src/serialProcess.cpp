
#include "Arduino.h"
#include "serialProcess.h"
#include "load.h"

void serialProcess :: sendVars(int th, int st) {
//  Serial1.println(st + "," + th);
}

int dataProcess :: processVars(int input, int upper, int lower, int deadzone, int upperPWM, int lowerPWM, int theoUpper, int theoLower) {
  //TODO: CHANGE HEADER FOR MAX/MIN VALUES
  int half = theoLower + (theoUpper - theoLower);
  if(input > (half-deadzone) && input < (half+deadzone)) {
    return //TODO ADD HALFPWM;
  }
<<<<<<< HEAD

  int presult = input - lower;
  int presult2 = (presult*100) / (range);
  int result = (presult*(upperPWM-lowerPWM))+lowerPWM;
  return result;
=======
>>>>>>> 064ffe423355d8f2f4903d6375d29c4624572bc8
}

void screenDataProcess::prepareScreenData(int *ptr) {

}

void screenSerialProcess::processCommand(String inString) {
  using namespace varStore;

  //TODO: ADD CODE TO SPLIT STRING INTO COMMAND AND MODIFIER(S)
  String command;
  String modifier;
  String value;

  if(command == "!deadzone") {

    if(modifier == "th") {
      TH_DEADZONE = value.toInt();;
    }else if(modifier == "st") {
      ST_DEADZONE = value.toInt();
    }

  } else if(command == "!max") {

    if(modifier == "th") {
      int half = (TH_OUT_THEO_UPPER - TH_OUT_THEO_LOWER)/2;
      float multiplier = (value.toInt())/100;
      TH_OUT_UPPER = TH_OUT_THEO_UPPER - (half*multiplier);
    }else if (modifier == "st") {
      int half = (ST_OUT_THEO_UPPER - ST_OUT_THEO_LOWER)/2;
      float multiplier = (value.toInt())/100;
      ST_OUT_UPPER = ST_OUT_THEO_UPPER - (half*multiplier);
      ST_OUT_LOWER = ST_OUT_THEO_LOWER + (half*multiplier);
    }

  }else if(command == "!min") {

    if(modifier == "th") {
      int half = (TH_OUT_THEO_UPPER - TH_OUT_THEO_LOWER)/2;
      float multiplier = (value.toInt())/100;
      TH_OUT_LOWER = TH_OUT_THEO_LOWER + (half*multiplier);
    }else if (modifier == "st") {
      int half = (ST_OUT_THEO_UPPER - ST_OUT_THEO_LOWER)/2;
      float multiplier = (value.toInt())/100;
      ST_OUT_UPPER = ST_OUT_THEO_UPPER - (half*multiplier);
      ST_OUT_LOWER = ST_OUT_THEO_LOWER + (half*multiplier);
    }

  }else if(command == "!invert") {

    if(modifier = "st") {
      if(value == "true") {
        stInvert = true;
      } else if (value == "false") {
        stInvert = false;
      }
    }

  } else {
    //TODO: add command formatter to serial process namespace
    screenDataProcess::outputString += ",!out -ERROR ILLEGAL COMMAND- src -cpuserproc85:87-,";
  }

}

void screenSerialProcess::sendOutputString() {
  Serial2.println(screenDataProcess::outputString);
}
