
#include <xc.h>

#include "common.h"

void OSC_config (void) 
{
    OSCCON = 0;
    OSCTUNE = 0x40; 
}

void TIMER0_config (void)
{
    T0CONbits.T08BIT = 1;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS0 = 1;
    T0CONbits.T0PS1 = 0;
    T0CONbits.T0PS2 = 1;
    
    INTCON = 0b11100100;
    
    T0CONbits.TMR0ON = 1;
}
void PORTA_config (void)
{
    ADCON1 |=0x0F;
    PORTAbits.RA0 = 0;
    LATAbits.LA0 = 0;
    TRISAbits.TRISA0 = 0;
}
void PORTC_config (void)
{
    PORTCbits.RC0 = 0;
    LATCbits.LC0 = 0;
    TRISCbits.TRISC0 = 0;
}