/*
 * File:   LedBlink.c
 * Author: rajat
 *
 * Created on January 3, 2018, 4:02 PM
 */
// DSPIC33EP32GP502 Configuration Bit Settings

// 'C' source line config statements

// FICD
#pragma config ICS = PGD1               // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FPOR
#pragma config ALTI2C1 = OFF            // Alternate I2C1 pins (I2C1 mapped to SDA1/SCL1 pins)
#pragma config ALTI2C2 = OFF            // Alternate I2C2 pins (I2C2 mapped to SDA2/SCL2 pins)
#pragma config WDTWIN = WIN25           // Watchdog Window Select bits (WDT Window is 25% of WDT period)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler bits (1:32,768)
#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
#pragma config PLLKEN = ON              // PLL Lock Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = ON              // Watchdog Timer Enable bit (Watchdog timer always enabled)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
#pragma config IOL1WAY = ON             // Peripheral pin select configuration (Allow only one reconfiguration)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)

// FOSCSEL
#pragma config FNOSC = FRCDIVN          // Oscillator Source Selection (Internal Fast RC (FRC) Oscillator with postscaler)
#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FGS
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GCP = OFF                // General Segment Code-Protect bit (General Segment Code protect is Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include "xc.h"

int main(void)
{
    TRISBbits.TRISB13 = 0;      //Port B 13 pin as output
    LATBbits.LATB13=0;          //Port B 13 pin initialised to 0
    T1CONbits.TON=0;            //Timer1 Stopped 
    T1CONbits.TCS=0;            //Timer Source Select bit ,to select the frquency source ,0=internal(Fosc/2),1=external
    T1CONbits.TGATE=0;          //Gated Timer disabled
    T1CONbits.TCKPS=0b10;       //1:8 Prescale selected 00=1:1,01=1:8,10=1:64,11=1:256
    TMR1=0X0000;                ///Timer 1 Register loaded with 0000
    PR1=0XFFFF;                 ///Period Register Loaded with FFFF
    IEC0bits.T1IE=1;            ///Timer 1 Interrupt enabled
    IPC0bits.T1IP=7;            //Timer 1 priority level set to 7,(0-7 increasing from lowest to highest being 7)
    IFS0bits.T1IF=0;            //Timer status flag cleared.
    T1CONbits.TON=1;            //Timer Started 
    while(1);
    
}
void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void)   //ISR Function
{
    LATBbits.LATB13=~LATBbits.LATB13;  //Port B 13th pin toggled 
    IFS0bits.T1IF=0;                   //Timer 1 Flag Cleared
    TMR1=0X0000;                       //Timer 1 Register Reset
    

}
