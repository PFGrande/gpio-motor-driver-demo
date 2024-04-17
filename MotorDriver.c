#include "MotorDriver.h"

int motorDriverHandle;

void initMotorDriver() {
    
    motorDriverHandle = i2cOpen(I2C_BUS, HAT_ADDR, 0);
}

void terminateMotorDriver() {
    i2cClose(motorDriverHandle);
}


/*
Frequency of 100 hz: 
pre_scale value = round(25MHz / [4096 * 100 Hz]) -1 = 60

Use presale value of 60 to get a frequency of 100 Hz
*/


// return 0 on success
// valid frequencies: 0-4095 (not as an input but as an actual value)
int setPWMfreq(int frequency) {
    i2cWriteByteData(motorDriverHandle, MODE_REGISTER_1, 0x10); // dissable the ocilator (set it to sleep mode) to 
    // change the pre_scale register (the ocilator's frequency)

    i2cWriteByteData(motorDriverHandle, PRE_SCALE_REGISTER, 0x3C);
    
    // wake up the ocilator after changing value
    i2cWriteByteData(motorDriverHandle, MODE_REGISTER_1, 0x00);
    
    // currently don't use frequency parameter, use testing variable
    // return i2cWriteByteData(motorDriverHandle, );
}