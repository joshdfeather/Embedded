#include "driverlib.h"
#include "device.h"
#include <stdio.h>

volatile uint16_t wave = 0;
volatile uint8_t flag = 0;

void timerINIT(void);
__interrupt void timerISR(void);

void main(void)
{
    Device_init();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    timerINIT();

    EINT;
    ERTM;

    while (1)
    {
        if (flag)
        {
            flag = 0;
            printf("Wave toggled to: %d\n", wave);
        }
    }
}

void timerINIT(void)
{
    CPUTimer_setPeriod(CPUTIMER0_BASE, DEVICE_SYSCLK_FREQ / 2000);
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);
    CPUTimer_stopTimer(CPUTIMER0_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    Interrupt_register(INT_TIMER0, &timerISR);
    Interrupt_enable(INT_TIMER0);

    CPUTimer_startTimer(CPUTIMER0_BASE);
}

__interrupt void timerISR(void)
{
    wave = !wave;
    flag = 1;

    CPUTimer_clearOverflowFlag(CPUTIMER0_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
