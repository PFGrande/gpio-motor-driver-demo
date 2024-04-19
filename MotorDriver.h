#include <pigpio.h>
#include "Channels.h"
#include <math.h>
#include <stdio.h>
// the motor hat uses bus 1
#define I2C_BUS 1

// Hat starts at address 0x40 on I2C bus 1
// sudo i2cdetect -y 1 to find address
#define HAT_ADDR 0x40

void initMotorDriver();
void terminateMotorDriver();

// not going to be public function, it is only here for testing
// sudo i2cget -y 1 0x40 0xFE used to see if value has actually been written
int setPWMfreq(int frequency);

void setPWMDutyCycle(int ledAddress, int dutyCycle);

void setChannelValue(int channel, int value);
