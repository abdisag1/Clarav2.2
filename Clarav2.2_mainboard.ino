#include "Clara.h"
#include "Levelsensors.h"
#include "Wata.h"
#include "Display.h"
#include "I2c.h"
#include "Voltagesensor.h"
#include <LiquidCrystal_I2C.h>       // Display driver
LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


//declaration of pins
using namespace std;
static byte pinA0 = A0;  // assigned for level sensor 1
static byte pinA1 = A1;  // assigned for level sensor 2
static byte pinA2 = A2;  // assigned for level sensor 3
static byte pinA3 = A3;  // assigned for voltage sensor

static byte pin3 = 3;    // assigned for flowmeter
static byte pin10 = 10;  // assigned for wata activation
static byte pin4 = 4;    // assigned for wata polarity reversal
static byte pin11 = 11;  // assigned for valve activation
static byte pin13 = 13;  // assigned for display obj
static byte pin14 = 14;


Clara clara;
Levelsensors level_sensors_obj(pinA0, pinA1, pinA2);
Wata wata_obj(pin10, pin4, pin11);
Display display_obj(pin13);
I2c i2c_obj(pin14);
Voltagesensor voltage_sensor_obj(pinA3);



void setup() {
  if (clara.read_state_from_EEPROM() == 3) {
    clara.pr_time_min = clara.read_min_from_EEPROM();
    
  }
  else if(clara.read_state_from_EEPROM() ==2){
    clara.pr_time_min = clara.default_pr_time_min;
  }
  else if(clara.read_state_from_EEPROM() ==4){
    clara.pr_time_min = clara.default_pr_time_min;
  }
  else if(clara.read_state_from_EEPROM() ==5){
    clara.pr_time_min = clara.default_pr_time_min;
  }
  lcd.init();
  lcd.begin(20, 4, LCD_5x8DOTS);
  lcd.backlight();
  Serial.begin(9600);
  //clara.pr_time_min = clara.read_min_from_EEPROM();


  // put your setup code here, to run once:
}

void loop() {

  level_sensors_obj.run(clara);
  wata_obj.run(clara);
  display_obj.run(clara, lcd);
  i2c_obj.run(clara);
  voltage_sensor_obj.run(clara);
  // put your main code here, to run repeatedly:
}
