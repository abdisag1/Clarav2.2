#ifndef MYI2C_H
#define MYI2C_H
#include "Clara.h"
#include "Eeprom.h"
#include <Wire.h>


using namespace std;

class I2c {
private:
  //Eeprom eeprom(13);
  byte pin_i2;
  

public:
  I2c(byte pin);

  void init();
  void run(Clara &clara);
};

#endif