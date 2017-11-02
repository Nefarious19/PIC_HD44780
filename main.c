
#include <xc.h>
#include <stdint.h>
#include "common.h"
#include "lcd.h"
#include "itoa.h"

void interrupt isr ();

uint_fast8_t tmr0 = 0;
uint8_t licznik = 0;
char buffer[20];
void main(void) 
{   
    OSC_config();
    PORTA_config();   
    
    lcd_init();
    lcd_locate(0,0);
    lcd_str("HD44780 LIB");
    lcd_locate(0,1);
    lcd_str("PIC18F4580");
    lcd_locate(0,2);
    lcd_str("By Nefarious19");
    lcd_locate(0,3);
    lcd_str("Licznik = ");
    TIMER0_config();
    while(1)
    {   
        if(!tmr0)
        {   
            
            LA0 ^= 1;
            tmr0 = 250;
            
            lcd_locate(10,3);
            lcd_str("          ");
            lcd_locate(10,3);
            lcd_str(itoa(licznik++,buffer));
        }
        
        
    }
}

void interrupt isr ()
{
   if(INTCONbits.TMR0IF == 1) 
   {    
      if(tmr0) tmr0--;
      TMR0L = 131;
      INTCONbits.TMR0IF = 0;
   }
}