/*
 * PROJECT:     FiveOS Kernel
 * LICENSE:     LGPL-3.0-or-later (https://spdx.org/licenses/LGPL-3.0-or-later.html)
 * PURPOSE:     Kernel entry point
 * COPYRIGHT:   Copyright 2021 Scott Maday <coldasdryice1@gmail.com>
 */

#include <fiveos.h>

PUCHAR Uart = (PUCHAR)0x10000000;

VOID PutChar(CHAR Char)
{
    while (*(Uart++))
    {
        *Uart = Char;
    }
}

VOID
Print(PCSTR String)
{
    while (*String != '\0')
    {
        PutChar(*String);
        String++;
    }
    return;
}

VOID
KernelEntry(VOID)
{
    Print("Hello world!\r\n");
    while(TRUE)
    {
        // Read input from the UART
        PutChar(*Uart);
    }
    return;
}