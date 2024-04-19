#include "MotorDriver.h"

int motorDriverHandle;

void initMotorDriver() {
    // gpioSetPWMrange(4095); // change the upper bound of the range to 4095,
    // this won't work, this is for a single pin, not the hat
    // the hat's range is already 4095
    
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
    prescaleCalc = floor(prescaleCalc);
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

// duty cycle accepts values 0% - 100%
void setPWMDutyCycle(int ledAddress, int dutyCycle) {
    // pg. 16 of documentation states 4095 is highest clock value in a cycle
    const double counterMax = 4095.00;

    // max % = 100
    double dutyPercentage = (dutyCycle % 100) / 100.00; // convert to decimal, then multiply duty cycle by it

    printf("duty percent: %f\n", dutyPercentage);

    dutyPercentage = counterMax * dutyPercentage;

    printf("duty percent II : %f\n", dutyPercentage);

    // round() caused values to round up. Floor rounds values down.
    dutyPercentage = floor(dutyPercentage);

    uint16_t pwmDutyCycle = dutyPercentage;
    
    // uint8_t too small
    // uint8_t pwmDutyCycle = dutyPercentage;

    printf("duty cycle: %u\n", pwmDutyCycle);

}

// find way to increment the channel
void setChannelValue(int channel, int value);

// taken from PCM9685 library: PCM9685.c file
void setPWM(uint8_t channel, uint16_t onTime, uint16_t offTime) {
    i2cWriteByteData(motorDriverHandle, LED0_ON_L + 4*channel, onTime & 0xFF); 
    i2cWriteByteData(motorDriverHandle, LED0_ON_H + 4*channel, onTime >> 8);
    PCA9685_WriteByte(motorDriverHandle, LED0_OFF_L + 4*channel, offTime & 0xFF);
    PCA9685_WriteByte(motorDriverHandle, LED0_OFF_H + 4*channel, offTime >> 8);
}