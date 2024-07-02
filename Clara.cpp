/*
list of global functions the main code
*/
#include "Clara.h"
using namespace std;



//initialization of methods
Clara::Clara() {
  init();
}

void Clara::init() {
  

}

float Clara::get_flow() {
  return flowrate;
}
void Clara::set_flow(float flowrate) {
  this->flowrate = flowrate;
}
// method to get the set point
float Clara::get_setpoint() {
  return set_point_global;
}

// function to set the setpoint
void Clara::set_setpoint(float setpoint) {

  this->set_point_global = setpoint;
}
// Function to read parameters value from EEPROM
float Clara::readParameterValueFromEEPROM(int state) {
  // Retrieve 4 bytes from EEPROM and convert back to float
  int address = state * sizeof(float);
  byte floatBytes[4];
  for (int i = 0; i < 4; i++) {
    floatBytes[i] = EEPROM.read(address + i);
  }
  union {
    float f;
    byte b[4];
  } convert;
  for (int i = 0; i < 4; i++) {
    convert.b[i] = floatBytes[i];
  }
  float retrievedFloat = convert.f;

  // Serial.println("Retrieved float value:");
  // Serial.println(retrievedFloat);
  return retrievedFloat;
}

// Function to write a parameter value to EEPROM
void Clara::writeParameterToEEPROM(int state, float parametervalue) {

  int address = state * sizeof(float);
  // Convert float to 4 bytes and store in EEPROM
  byte floatBytes[4];
  union {
    float f;
    byte b[4];
  } convert;
  convert.f = parametervalue;
  for (int i = 0; i < 4; i++) {
    EEPROM.write(address + i, convert.b[i]);
  }
  // Serial.println("Stored float value:");
  // Serial.println(parametervalue);
}

// function to write the state value to EEPROM
void Clara:: write_state_to_EEPROM(int state_value) {
  // I chose address 64 to save the state value at.
  int address =  64;
  EEPROM.write(address, state_value);
  Serial.println("The state value is saved to EEPROM ");
}

// Function to read the state value from EEPROM
int Clara:: read_state_from_EEPROM() {
  int address = 64;
  return EEPROM.read(address);
}
// function to write production time and valve opening time
void Clara:: write_min_to_EEPROM(int minutes){
  int address = 68;
  return EEPROM.write(address,minutes);
}
int Clara:: read_min_from_EEPROM() {
  int address = 68;
  return EEPROM.read(address);
}


int Clara::get_liquidlevel_1() {
  return liquidlevel_1;
}
void Clara::set_liquidlevel_1(int liquidlevel_1) {
  this->liquidlevel_1 = liquidlevel_1;
}

int Clara::get_liquidlevel_2() {
  return liquidlevel_2;
}
void Clara::set_liquidlevel_2(int liquidlevel_2) {
  this->liquidlevel_2 = liquidlevel_2;
}
int Clara::get_liquidlevel_3() {
  return liquidlevel_3;
}
void Clara::set_liquidlevel_3(int liquidlevel_3) {
  this->liquidlevel_3 = liquidlevel_3;
}
int Clara::get_state() {
  return state;
}
void Clara::set_state(int state) {
  this->state = state;
}
// functions to set and get voltage

float Clara:: get_voltage() {
  return voltage;
}
void Clara:: set_voltage(float voltage) {
  this->voltage = voltage;
}

