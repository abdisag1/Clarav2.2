#ifndef MY_CLARA_H
#define MY_CLARA_H
#include <EEPROM.h>  // Include EEPROM library

#include "Arduino.h"


using namespace std;

class Clara {


private:
  float flowrate = 0;
  float set_point_global = 0;
  byte state = 0;


public:
  Clara();
  void init();
  int state_standby=2;
  int state_production=3;
  int state_settling =4;
  int state_transfering_fluid =5;

  
  int liquidlevel_1 = 1;
  int liquidlevel_2 = 1;
  int liquidlevel_3 = 1;
  float voltage;
  float get_flow();
  void set_flow(float flowrate);
  float get_setpoint();
  void set_setpoint(float setpoint);
  int get_state();
  void set_state(int state);
  // functions to read and write from the eeprom
  float readParameterValueFromEEPROM(int state);
  void writeParameterToEEPROM(int state, float parametervalue);
  void write_state_to_EEPROM(int state_value);
  int read_state_from_EEPROM();
  void write_min_to_EEPROM(int minutes);
  int read_min_from_EEPROM();
  int get_liquidlevel_1();
  void set_liquidlevel_1(int liquidlevel_1);
  int get_liquidlevel_2();
  void set_liquidlevel_2(int liquidlevel_2);
  int get_liquidlevel_3();
  void set_liquidlevel_3(int liquidlevel_3);
  float get_voltage();
  void set_voltage(float voltage);
  float c_flowrate = 0;
  // variables to communicate between the two boards
  float flow_ratio = 1;
  float target_frc = 1.5;
  float target_naclo_con = 4.5;
  float ki = 2.5;
  float kp = 2;
  float feed_back_interval = 3000;
  float correction_factor = 1;
  unsigned int pr_time_min = 6;
  unsigned int default_pr_time_min =6;
  int liquid_tranfer_min = 10;
  int settling_min = 5;
};
#endif