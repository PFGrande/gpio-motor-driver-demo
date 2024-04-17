#include <pigpio.h>
#include "Channels.h"
// the motor hat uses bus 1
#define I2C_BUS 1

// Hat starts at address 0x40 on I2C bus 1
// sudo i2cdetect -y 1 to find address
#define HAT_ADDR 0x40

void initMotorDiver();
void terminateMotorDriver();