/*
 * File:   PIC_SPI.c
 * Author: Aswinth Raj B
 * For using SPI communication with PIC16F877a
 * Created on 15 May, 2018, 1:46 PM
 */

/*This header file covers only the use of SPI in OSC/64, middle sample, active to ideal clock mode.
 * You can configure the SSPSTAT and SSPCON registers to get the SPI working in different modes
 */

void SPI_Initialize_Master()
{
     TRISC5 = 0; //
     SSPSTAT = 0b11000000; //pg 74/234
     SSPCON = 0b00100000; //pg 75/234
     TRISC3 = 0; //Set as output for slave mode 
}

void SPI_Initialize_Slave()
{
     TRISC5 = 0; // SDO pin should be declared as output 
     SSPSTAT = 0b00000000; //pg 74/234
     SSPCON = 0b00100000; //pg 75/234
     TRISC3 = 1; //Set as in out for master mode
}


void SPI_Write(char incoming) 
{
    SSPBUF = incoming; //Write the user given data into buffer
    while (!SSPSTATbits.BF);
}

unsigned SPI_Ready2Read()
{
    if (SSPSTAT & 0b00000001)
        return 1;
    else
        return 0;
}

char SPI_Read() //Read the received data
{
    while ( !SSPSTATbits.BF ); // Hold till BF bit is set, to make sure the complete data is read
    return(SSPBUF); // return the read data
}