#include "driverlib.h"
#include "device.h"
#include <stdio.h>

volatile uint8_t hours = 12;
volatile uint8_t minutes = 53;
volatile uint8_t seconds = 11;
char buffer[20];

void clockINIT(void);
__interrupt void clockISR(void);

void main(void)
{
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    clockINIT();

    EINT;
    ERTM;

    while (1)
    {
        sprintf(buffer, "Time: %02d:%02d:%02d\n", hours, minutes, seconds);
        printf("%s", buffer);
        DEVICE_DELAY_US(500000);
    }
}

void clockINIT(void)
{
    CPUTimer_setPeriod(CPUTIMER0_BASE, DEVICE_SYSCLK_FREQ / 2);
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);
    Interrupt_register(INT_TIMER0, &clockISR);
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    Interrupt_enable(INT_TIMER0);
    CPUTimer_startTimer(CPUTIMER0_BASE);
}

__interrupt void clockISR(void)
{
    seconds++;
    if (seconds >= 60)
    {
        seconds = 0;
        minutes++;
        if (minutes >= 60)
        {
            minutes = 0;
            hours++;
            if (hours >= 24)
            {
                hours = 0;
            }
        }
    }
    CPUTimer_clearOverflowFlag(CPUTIMER0_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
