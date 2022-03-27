#include <EEPROM.h> //Import the EEPROM library for using the EEPROM commands

//-------------- Variable Definitions --------------

int address; //Create variable to store current address
int delayNum = 1000; //Set time for delay

byte value = 1; //Create variable to act as a buffer for the written EEPROM value

bool lock = 0; //Create variable to make sure that the read process does not run twice

//-------------- Function Definitions --------------

int FindNextAddress(int startAddress) {
  for (int i = startAddress; i < EEPROM.length(); i++) { //Start stepping through each EEPROM address
    if (EEPROM.read(i) == 0) { //If the byte has not been written
      address = i;
      return address; //Return the address
    }
  }
}

//-------------- Main Code --------------

void setup() {
  pinMode(0, INPUT); //Declare the jumper pin as an input
  address = FindNextAddress(0); //Set the address to the next available address
  EEPROM.write(address, 255);
  address++;
  EEPROM.write(address, value);
}

void loop() {
  if ((digitalRead(1) == LOW) && (address < EEPROM.length())) {  //Check if jumper is unplugged and EEPROM is not full

    //------ Logic for Write ------
    value++;
    if (value >= 255) {
      address++;
      value = 1;
    }
    EEPROM.write(address, value);
    if (time == 10) {
      delayNum = delayNum * 10; //once we get 10 seconds in, increase delay time
    }
    delay(delayNum);

  }


  //------ Logic for Read ------
  else { //If the jumper is plugged in
    if (!lock) { //If the value is not locked
      for (int i = 0; i < EEPROM.length(); i++) { //Step through every address in the EEPROM
        //Serial.println((int)EEPROM.read(i)); //Print each value in the EEPROM
      }
      lock = 1; //Lock the read function so it dosen't read recursivly
    }
  }
}
