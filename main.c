#include "MotorDriver.h"
#include <stdio.h>

int main () {
    if (gpioInitialise() < 0) {
        printf("pigpio initialization failed\n");
        return 0;
    } else {
        printf("pigpio initialization successful\n");
    }

    initMotorDriver();
    setPWMfreq(100); // IT WORKED





    // kill pigpio daemon (will not run if program crashes)
    gpioTerminate();
}