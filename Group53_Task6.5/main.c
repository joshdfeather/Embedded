
#include "driverlib.h"
#include "device.h"


#define BUTTON_LED_PIN   31U
#define ACTION_LED_PIN   34U

volatile bool button = false;
__interrupt void gpioInterrupt(void);


void main(void)
{
    Device_init();
    Device_initGPIO();

    GPIO_setPadConfig(BUTTON_LED_PIN, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(BUTTON_LED_PIN, GPIO_DIR_MODE_OUT);
    GPIO_writePin(BUTTON_LED_PIN, 1);

    GPIO_setPadConfig(ACTION_LED_PIN, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(ACTION_LED_PIN, GPIO_DIR_MODE_OUT);
    GPIO_writePin(ACTION_LED_PIN, 0);

    GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_FALLING_EDGE);
    GPIO_setInterruptPin(BUTTON_LED_PIN, GPIO_INT_XINT1);
    GPIO_enableInterrupt(GPIO_INT_XINT1);

    Interrupt_initModule();
    Interrupt_initVectorTable();
    Interrupt_register(INT_XINT1, &gpioInterrupt);
    Interrupt_enable(INT_XINT1);

    EINT;
    ERTM;

    while (1)
    {
        if (button)
        {
            button = false;
            GPIO_togglePin(ACTION_LED_PIN);
        }
        DEVICE_DELAY_US(2000000);
        GPIO_togglePin(BUTTON_LED_PIN);
    }
}

__interrupt void gpioInterrupt(void)
{
    button = true;
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
