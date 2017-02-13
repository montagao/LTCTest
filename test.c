/*
 * Basic test to familiarize myself with Arduino (C?) syntax
 * and initializing SPI communications using Arduino
 *
 *
 * Basic Pin Configuration:
 *
 * SS       :53
 * MOSI pin :51 
 * MISO pin :50
 * SCK (CLK):52
 * 
 */


#include <SPI.h>

#define slaveSelectPin 53

#define WRCFG 0x01
#define RDCFG 0x02
#define RDCV 0x04




byte byteTemp;

void setup(){
    // SPI library only supports master mode so we should set pin to OUTPUT 
    pinMode(slaveSelectPin, OUTPUT);

    digitalWrite(slaveSelectPin, HIGH);
    SPI.setBitOrder(MBBFIRST);
    SPI.setDataMode(SPI_MODE3);

    // SPI.setClockDivider(SPI_CLOCK_DIV16);
    // Serial.begin(9600);
    //writeREg();



    SPI.begin();
}

void writeConfig(){

    digitalWrite(slaveSelectPin, LOW);

    // write configuration registers
    SPI.transfer( 0x00 );
    SPI.transfer( 0x01 );

    SPI.transfer( 0x3D );
    SPI.transfer( 0x6E );

    // send cfgr0 byte 


}

void loop(){


    // write a simple command to read internal DIE of the device
    // and output it to console

    // send a dummy byte , activity on CSB and SCK will wake up the serial device
    ltcWrite( 0x00 ); 

    // wait amount tWake max (0.3 milliseconds)
    delay( 1 ); 

    // send a second dummy byte and wait for tready in case of IDLE


    //Write config registers

}


/*
 * broadcast command codes have a value of 0 for CMD0[7] through CMD0[3]
 * And have the format of : 
 *   [8]    [8]     [8]     [8]     [8] ............ [8]                [8]     [8]     [8]
 *  [CMD0]  [CMD1]  [PEC0]  [PEC1]  [Databyte Low]  [Data byte high]    [PEC0]  [PEC1]  [shift byte 1]
 *
 */





int getInternalTemp(){

    // pull CSB low
    digitalWrite( slaveSelectPin, LOW );

    /* send ADSTAT command (0x05, 0x6A and its PEC 0x , 0x48)
       with parameter to get ITMP
       ADSTAT : 0b10 MD[1] MD[0] 1 1 0 1 CHST [2] CHST[1] CHST[0]
       for ITMP we need : MD = 10 (Normal ADC mode)
       and CHST[2:0] = 010
       SDO or MISO will be LOW if the LTC6804-2 chip is busy
    */
    SPI.transfer(0x05);
    SPI.transfer(0x6A);
    
    SPI.transfer16( 0x9F14 );

    SPI.transfer16( 0x1C48 );

    // allow delay for conversion time
    delay( 1 );

    // de-select SS pin
    digitalWrite( slaveSelectPin, HIGH);

    byte ITMP[4];

    for( int i = 0; i < 4; i++ ){
        ITEMP[i] = SPI.transfer( 0x00 ); // read the value by sending dummy bytes? 
        Serial.println( ITEMP[i] );
    }


}

// get PEC 
// can use this in the future to get the PEC values for commands 
// instead of inputting the manually
byte getPEC(){
    // TODO:

}

