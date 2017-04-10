//include screen lib so i can retain similarity between my repos
#include <Adafruit_ILI9341.h>

//include my external files
#include "serialProcess.h" //manages serial setup and interface with reciever
#include "screen.h" //manages interface with screen
#include "load.h" //contains details on variables, etc

//TODO: CHANGE THESE OBJECTS TO BE NAMESPACES
// create instances of external objects
serialProcess io;
dataProcess data;

//import namepaces used for file storage in various areas of program
using namespace toggles;
using namespace pins; //stores data on pin assignments
using namespace varStore; //stores general data (ie constraints for inputs/outputs)


//init vars for sensor values
int ldrValue;
bool tiltValue;

void setup() {
  load::modeSet(); //sets pin modes
  load::serialSetup(); //initialises appropriate serial connections
}

void loop() {

  //processes data to be output to throttle
  int thOut = data.processVars(analogRead(throttle),TH_IN_UPPER,
      TH_IN_LOWER, TH_DEADZONE, TH_OUT_UPPER, TH_OUT_LOWER, TH_OUT_THEO_UPPER, TH_OUT_THEO_LOWER);

  //processes data to be output to steering servo
  //int stOut = data.processVars(analogRead(steer), ST_IN_UPPER,
  //    ST_IN_LOWER, ST_DEADZONE, ST_OUT_UPPER, ST_OUT_LOWER, ST_OUT_THEO_UPPER, ST_OUT_THEO_LOWER);
  int stOut = 0;
  io.sendVars(thOut, stOut); //sends vars to reciever

  if ((millis() % 50) == 0) { //sends data to screen every 50ms
    screenSerialProcess::sendOutputString(); //sends miscellaneous data to screen

    //creates an array and a pointer to it
    int outArray[1];
    int *outPtr;
    outPtr = &outArray[0];

    screenDataProcess::prepareScreenData(outPtr); //prepares telemetry data to be sent to screen
  }
  if(toggles::test == true) {
    delay(100);
  }
}

//recieves and processes data from car
void serialEvent1() {
   while (Serial.available()) {
     //recieves tilt sensor value
     tiltValue = Serial.readStringUntil(',').toInt();
     Serial.read(); //reads comma and ignores it

     //recieves LDR value
     ldrValue = Serial.readStringUntil(',').toInt();
     Serial.readStringUntil('\n'); //clears buffer
   }
}

//recieves and processes data from graphics coprocessor
void serialEvent2() {
  //collects input data
  String inString = Serial.readStringUntil('\n');

  //checks if input is a command
  if (inString.startsWith("!")) { //command processor for changing settings at present
    screenSerialProcess::processCommand(inString); //processes command
  }else {
    //adds an error to output stack to screen
    screenDataProcess::outputString += "!out -ERROR NOT A COMMAND- src -cpumain58:81-,";
  }
}
