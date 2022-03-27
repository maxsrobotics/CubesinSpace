#include <EEPROM.h>
#include <DigiKeyboard.h>

bool validated = 1;

void setup() {
  //Serial.begin(9600);
  
  for(int i=0; i<EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
  DigiKeyboard.println("All cleared (I think)! Anyhow, validating clear!");
  for(int i=0; i<EEPROM.length(); i++) {
    if(EEPROM.read(i) == 0) {
      continue;
    }
    else {
      validated = 0;
      DigiKeyboard.print(i);
      DigiKeyboard.println(" failed to clear");
    }
  }
  if(validated) {
    DigiKeyboard.println("All clear!");
  }
}

void loop() {
    
}
