#ifndef serialProcess_h
#define serialProcess_h

#include "Arduino.h"

class serialProcess {
public:
    void sendVars(int th, int st);
};

class dataProcess {
public:
  int processVars(int input, int upper, int lower, int deadzone, int upperPWM, int lowerPWM);
};

namespace screenDataProcess {
  static String outputString;
  void prepareScreenData(int *processArray);

}

namespace screenSerialProcess {
  void sendToScreen(int *processArray);
  void processCommand(String inString);
  void sendOutputString();
}


#endif
