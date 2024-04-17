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

/* " fixed frequency individual PWM controller that 
operates at a programmable frequency from a typical 
of 40 Hz to 1000 Hz " */
int setPWMfreq(int frequency) {
    const double oscillatorClockFreq = 25000000.0; // 25 MHz -> Hz

    // prescaleValue equation:
    double prescaleCalc = oscillatorClockFreq / (4096.0 * frequency);
    prescaleCalc = round(prescaleCalc);
    prescaleCalc -= 1;

    // convert end result to unsigned int
    uint8_t prescaleValue = prescaleCalc;

    printf("prescaleValue: %u", prescaleValue);


    i2cWriteByteData(motorDriverHandle, MODE_REGISTER_1, 0x10); // dissable the ocilator (set it to sleep mode) to 
    // change the pre_scale register (the ocilator's frequency)

    // uint8_t test = 60; //0x3C;
    i2cWriteByteData(motorDriverHandle, PRE_SCALE_REGISTER, prescaleValue);

    // wake up the ocilator after changing value
    i2cWriteByteData(motorDriverHandle, MODE_REGISTER_1, 0x00);
    
    // currently don't use frequency parameter, use testing variable
    // return i2cWriteByteData(motorDriverHandle, );
}