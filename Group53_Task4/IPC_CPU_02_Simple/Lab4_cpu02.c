// FILE:   Lab4_cpu02.c

#include "F28x_Project.h"
#include <stdio.h>
#include <math.h>

// Define an array to receive data
unsigned long received[20];
volatile unsigned long *pointer;

// Function Prototypes
interrupt void ipc2_isr(void);

void main(void)
{
    InitSysCtrl();
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    EALLOW;
    PieVectTable.IPC1_INT = &ipc2_isr;
    EDIS;

    IpcRegs.IPCCLR.bit.IPC0 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    PieCtrlRegs.PIEIER1.bit.INTx14 = 1;

    IER |= M_INT1;
    EINT;
    ERTM;

    // Signal CPU1 that CPU2 is ready
    IpcRegs.IPCSET.bit.IPC17 = 1;

    // Wait indefinitely
    while(1)
    {

    }
}

interrupt void ipc2_isr(void)
{
    // Set pointer to shared memory
    pointer = (unsigned long *)0x3FC00;

    // Copy data from shared memory to local array
    int i;
    for (i = 0; i < 20; i++) {
        received[i] = pointer[i];
        printf("CPU2: Received[%d] = %lu\n", i, received[i]);
    }

    // Clear IPC flag and acknowledge interrupt
    IpcRegs.IPCACK.bit.IPC1 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

// end of file
