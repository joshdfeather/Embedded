
#include "driverlib.h"
#include "device.h"
#include <stdio.h>

#define ARRAY_SIZE 100  // Define the array size for transfer
#define BURST       10      // DMA burst size
#define TRANSFER    10      // DMA transfer size

volatile uint16_t done;     // Transfer completion flag

#pragma DATA_SECTION(array_1, "DMARAM1")  // Place array_1 in DMA-accessible RAM
#pragma DATA_SECTION(array_2, "DMARAM2")  // Place array_2 in DMA-accessible RAM

uint16_t array_1[ARRAY_SIZE] = {  // Initialise array_1
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
    51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
    61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
    71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
    81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
    91, 92, 93, 94, 95, 96, 97, 98, 99, 100
};
uint16_t array_2[ARRAY_SIZE];  // Declare an empty array_2

__interrupt void DMA_ISR(void);  // ISR for DMA interrupt
void DMA_INIT(void);             // DMA initialisation function

void main(void)
{
    // Initialise device and interrupt systems
    Device_init();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    Interrupt_register(INT_DMA_CH1, &DMA_ISR);

    // Enable DMA interrupt on channel 1
    Interrupt_enable(INT_DMA_CH1);
    EINT;

    // Initialise DMA settings
    DMA_INIT();

    // Start DMA channel 1
    DMA_startChannel(DMA_CH1_BASE);

    done = 0;  // Clear the done flag
    while(!done)  // Wait until the DMA ISR completes
    {
        DMA_forceTrigger(DMA_CH1_BASE);  // Force DMA trigger to start the transfer
        DEVICE_DELAY_US(1000);           // Small delay for triggering the DMA
    }
    ESTOP0;  // Stop execution (used for debugging, halts the processor)
}


void DMA_INIT()
{
    // Initialise DMA controller
    DMA_initController();

    // Set up source and destination pointers for DMA
    const void *source = (const void *)array_1;
    const void *destination = (const void *)array_2;

    // Configure the DMA addresses for source and destination
    DMA_configAddresses(DMA_CH1_BASE, destination, source);

    // Configure DMA settings
    DMA_configBurst(DMA_CH1_BASE, BURST, 1, 1);  // Set burst size and increment steps
    DMA_configTransfer(DMA_CH1_BASE, TRANSFER, 1, 1);  // Set transfer size and steps
    DMA_configMode(DMA_CH1_BASE, DMA_TRIGGER_SOFTWARE, DMA_CFG_ONESHOT_DISABLE);  // Set software trigger and disable one-shot
    DMA_setInterruptMode(DMA_CH1_BASE, DMA_INT_AT_END);  // Set interrupt mode to trigger at the end of the transfer
    DMA_enableTrigger(DMA_CH1_BASE);  // Enable the DMA trigger
    DMA_enableInterrupt(DMA_CH1_BASE);  // Enable interrupt for this DMA channel
}


__interrupt void DMA_ISR(void)
{
    // Stop DMA channel after completion
    DMA_stopChannel(DMA_CH1_BASE);

    EALLOW;
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);  // Acknowledge and clear the interrupt for Group 7
    EDIS;

    // Loop through and print the values of array_1 and array_2 for verification, stopping if failed
    int i;
    for(i = 0; i < 100; i++)
    {
        printf("array_1[%d] = %d\n", i, array_1[i]);
        printf("array_2[%d] = %d\n", i, array_2[i]);
        if (array_2[i] != array_1[i]) {
            ESTOP0;
        }

    }
    done = 1;
    return;  // Return from ISR
}

//
// End of file
//
