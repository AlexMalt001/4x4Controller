
#include "Arduino.h"
#include "serialProcess.h"
#include "load.h"



void serialProcess :: sendVars(int th, int st) {
  Serial1.println(String(st) + "," + String(th));
  if (toggles::test == 1) {
    Serial.println(String(st) + ", " + String(th));
  }
}

int dataProcess :: processVars(int input, int upper, int lower, int deadzone, int upperPWM, int lowerPWM, int theoUpper, int theoLower) {

  int halfIn = lower + ((upper - lower)/2);
  int halfPWM = theoLower + ((theoUpper - theoLower)/2);
  if(input > (halfIn-deadzone) && input < (halfIn+deadzone)) {
    return halfPWM;
  }

  if (input > halfIn) {
    return constrain(map(input, halfIn+deadzone, upper, halfPWM, upperPWM), halfPWM, upperPWM);
  } else {
    return constrain(map(input, lower, halfIn-deadzone, lowerPWM, halfPWM), lowerPWM, halfPWM);
  }
}

void screenDataProcess::prepareScreenData(int *ptr) {
  //TODO: ALL THE THINGS
}

void screenSerialProcess::processCommand(String inString) {
  using namespace varStore;

  //init vars for components of command
  String command;
  String modifier;
  String value;

  //Split input String into command, modifier and value
  String workingString = inString;
  workingString.remove(0); //remove '!'
  command = workingString.substring(0,inString.indexOf(' ')); // seperate command portion (keyword)
  workingString.remove(0,inString.indexOf(' ')); //remove command from working String
  modifier = workingString.substring(0, inString.indexOf(' '));//seperate modifier portion
  workingString.remove(0,inString.indexOf(' ')); //remove modifier from working String
  value = workingString;


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
    screenDataProcess::outputString += "!out -ERROR ILLEGAL COMMAND- src -cpuserproc85:87-,";
  }

}

void screenSerialProcess::sendOutputString() {
  Serial2.println(screenDataProcess::outputString);
}
