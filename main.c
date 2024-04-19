#include "MotorDriver.h"
#include <stdio.h>
#include <unistd.h>

#define IN1 PCA_CHANNEL_1
#define IN2 PCA_CHANNEL_2
#define PWM PCA_CHANNEL_0
#define MICROSEC_IN_SEC 1000000

int main () {
    if (gpioInitialise() < 0) {
        printf("pigpio initialization failed\n");
        return 0;
    } else {
        printf("pigpio initialization successful\n");
    }

    initMotorDriver();
    setPWMfreq(100); // IT WORKED

    //m
    // setPWMDutyCycle(0, 50);
    // setPWMDutyCycle(0, 0);

    // should be PWM channel
    // setPWMDutyCycle(0, 50);

    setPWMDutyCycle(PWM, 50);

    printf("WROTE TO CHANNEL 0\n");

    usleep(5 * MICROSEC_IN_SEC);
    setLevel(IN1, 1);
    setLevel(IN2, 0);
    printf("WROTE FORWARDS\n");

    usleep(3 * MICROSEC_IN_SEC);

    setLevel(IN1, 0);
    setLevel(IN2, 1);

    printf("WROTE backwards\n");
    usleep(3 * MICROSEC_IN_SEC);

    setLevel(IN1, 0);
    setLevel(IN2, 0);

    printf("MOTOR SHOULD BE OFF\n");

    // kill pigpio daemon (will not run if program crashes)
    terminateMotorDriver();
    gpioTerminate();
}