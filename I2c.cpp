#include "I2c.h"

using namespace std;
I2c::I2c(byte pin_i2c) {
  this->pin_i2;
  init();
}


void I2c::init() {
 Wire.begin();
  Serial.begin(9600);
}


void I2c::run(Clara &clara) {

  Wire.requestFrom(0x21, sizeof(float) * 8);  // Request data from slave

  float receivedData[2];
  Wire.readBytes((uint8_t*)receivedData, sizeof(receivedData));

  // Process the received data (e.g., print it)
  for (int i = 0; i < 2; i++) {
    // Serial.print("Received data ");
    // Serial.print(i);
    // Serial.print(": ");
    // Serial.println(receivedData[i], 2);  // Print with 2 decimal places
    // clara.set_flow(receivedData[1]);
    // clara.set_setpoint(receivedData[0]);
  }
  // part of code that sends data to the slave
  // Create an array of 8 float variables
  float dataToSend[8] = { 1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1 };
  dataToSend[0]= clara.flow_ratio;
  dataToSend[1]= clara.target_frc;
  dataToSend[2] = clara.target_naclo_con;
  dataToSend[3] = clara.ki;
  dataToSend[4] = clara.kp;
  dataToSend[5] = clara.feed_back_interval;
  dataToSend[6] = clara.correction_factor;
  

  // // Send the data to the slave
  Wire.beginTransmission(0X21); // Slave address
  Wire.write((uint8_t*)dataToSend, sizeof(dataToSend));
  Wire.endTransmission();
  // send of the transmission to the slave


}
  