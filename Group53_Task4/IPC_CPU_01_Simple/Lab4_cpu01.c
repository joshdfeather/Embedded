// FILE: Lab4_cpu01.c

#include "F28x_Project.h"
#include <stdio.h>

// Define an array to send data
unsigned long array[20] = {
    10, 11, 12, 13, 14,
    15, 16, 17, 18, 19,
    20, 21, 22, 23, 24,
    25, 26, 27, 28, 30
};
volatile unsigned long *pointer;

// Function Prototypes
interrupt void ipc1_isr(void);

void main(void)
{
    InitSysCtrl();
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    EALLOW;
    PieVectTable.IPC0_INT = &ipc1_isr;
    EDIS;

    IpcRegs.IPCCLR.all = 0xFFFFFFFF;

    // Enable PIE interrupts
    PieCtrlRegs.PIEIER1.bit.INTx13 = 1;

    IER |= M_INT1;
    EINT;
    ERTM;

    // Wait for CPU02 to signal readiness
    while (IpcRegs.IPCSTS.bit.IPC17 == 0);
    IpcRegs.IPCACK.bit.IPC17 = 1;

    // Set pointer to the start of shared memory
    pointer = (unsigned long *)0x3FC00;

    // Copy array data to shared memory
    int i;
    for (i = 0; i < 20; i++) {
        pointer[i] = array[i];
    }

    // Signal CPU2 that data is ready
    IpcRegs.IPCSET.bit.IPC1 = 1;
}

interrupt void ipc1_isr(void)
{
    IpcRegs.IPCACK.bit.IPC0 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


