#include "MotorDriver.h"

int motorDriverHandle;

void initMotorDriver() {
    
    motorDriverHandle = i2cOpen(I2C_BUS, HAT_ADDR, 0);
}

void terminateMotorDriver() {
    i2cClose(motorDriverHandle);
}

// return 0 on success
// valid frequencies: 0-4095 (not as an input but as an actual value)
int setPWMfreq(int frequency) {
    i2cWriteByteData(); // dissable the ocilator (set it to sleep mode) to 
    // change the pre_scale register (the ocilator's frequency)
    // currently don't use frequency parameter, use testing variable
    // return i2cWriteByteData(motorDriverHandle, );
}