
#include <xc.h>
#include <stdint.h>
#include "lcd.h"
#include "common.h"

static uint8_t _check_bf (void);

static void _port_init (void)
{
        LCD_E_PORT   = 0;
        LCD_RW_PORT  = 0;
        LCD_RS_PORT  = 0; 
        LCD_D4_PORT  = 0;
        LCD_D5_PORT  = 0;
        LCD_D6_PORT  = 0;
        LCD_D7_PORT  = 0; 
        
        
        LCD_E_LAT   = 0;
        LCD_RW_LAT  = 0;
        LCD_RS_LAT   = 0; 
        LCD_D4_LAT   = 0;
        LCD_D5_LAT  = 0;
        LCD_D6_LAT   = 0;
        LCD_D7_LAT  = 0; 
        
        
        LCD_E_TRIS   = 0;
        LCD_RW_TRIS  = 0;
        LCD_RS_TRIS  = 0; 
        LCD_D4_TRIS  = 0;
        LCD_D5_TRIS  = 0;
        LCD_D6_TRIS  = 0;
        LCD_D7_TRIS  = 0;   
}

static void _data_dir_out(void)
{
    LCD_D4_TRIS = 0;
    LCD_D5_TRIS = 0;
    LCD_D6_TRIS = 0;
    LCD_D7_TRIS = 0;
}

static void _data_dir_in(void)
{
    LCD_D4_TRIS = 1;
    LCD_D5_TRIS = 1;
    LCD_D6_TRIS = 1;
    LCD_D7_TRIS = 1;
}

static void _lcd_send_half (uint8_t data)
{
  if (data & (1<<0)) LCD_D4_LAT = 1;
  else LCD_D4_LAT = 0;
  
  if (data & (1<<1)) LCD_D5_LAT = 1;
  else LCD_D5_LAT = 0;
  
  if (data & (1<<2)) LCD_D6_LAT = 1;
  else LCD_D6_LAT = 0;
  
if (data & (1<<3)) LCD_D7_LAT = 1;
  else LCD_D7_LAT = 0;  
}

static uint8_t _lcd_read_half (void)
{
  uint8_t data = 0;
  
  if(LCD_D4_PORT) data |= (1<<0);
  if(LCD_D5_PORT) data |= (1<<1);
  if(LCD_D6_PORT) data |= (1<<2);
  if(LCD_D7_PORT) data |= (1<<3);
  
  return data;
}

static void _lcd_send_byte (uint8_t data)
{
    _data_dir_out();
    LCD_WRITE;
   
    
    
    _lcd_send_half((uint8_t)(data>>4));
    SET_E;
    __delay_us(1);
    CLR_E;
    __delay_us(1);
    
    _lcd_send_half((uint8_t)data);
    __delay_us(1);
    SET_E;
    __delay_us(1);
    CLR_E;
    __delay_us(1); 
    
    while( (_check_bf() & (1<<7)) );
}

static  uint8_t _lcd_read_byte (void)
{
    uint8_t data = 0;
    _data_dir_in();    
    LCD_READ;
    __delay_us(1);
    
    SET_E;
    __delay_us(1);    
    CLR_E;
    __delay_us(1);
    data = (uint8_t)(4  <<  ((uint8_t)_lcd_read_half()) );
    __delay_us(1);
     
    SET_E;
    __delay_us(1);    
    CLR_E;
    __delay_us(1);
    data |= (uint8_t)(((uint8_t)_lcd_read_half()));
     __delay_us(1);
    
    return data;
    
}



static uint8_t _check_bf (void)
{
    LCD_COMMAND;
    return _lcd_read_byte();
}

void lcd_send_command (uint8_t data)
{
    LCD_COMMAND;
    _lcd_send_byte(data);
    __delay_ms(1);
}

void lcd_send_data (uint8_t data)
{
    LCD_DATA;
    _lcd_send_byte(data);
    __delay_ms(1);
}

void lcd_init(void)
{   
     _port_init();
     _data_dir_out();
     LCD_E_TRIS = 0;
     LCD_RS_TRIS = 0;
     LCD_RW_TRIS = 0;
     __delay_us(5);
     
     LCD_E_LAT = 1;
     LCD_RW_LAT = 1;
     LCD_RS_LAT = 1;
     
     
     __delay_ms(15);
     
     LCD_E_LAT = 0;
     LCD_RW_LAT = 0;
     LCD_RS_LAT = 0;
     
     _lcd_send_half(0x03);
     SET_E;
     __delay_us(100);
     CLR_E;
     __delay_ms(5);     
     
       _lcd_send_half(0x03);
     SET_E;
     __delay_us(100);
     CLR_E;
    __delay_ms(5);   
    
      _lcd_send_half(0x03);
     SET_E;
     __delay_us(100);
     CLR_E;
     __delay_ms(5);   
    
     _lcd_send_half(0x02);
     SET_E;
     __delay_us(100);
     CLR_E;
     __delay_ms(5);   
     
     // ju? mo?na u?ywa? Busy Flag
	// tryb 4-bitowy, 2 wiersze, znak 5x7
	lcd_send_command( LCDC_FUNC|LCDC_FUNC4B|LCDC_FUNC2L|LCDC_FUNC5x7 );
	// wy??czenie kursora
	lcd_send_command( LCDC_ONOFF|LCDC_CURSOROFF );
	// w??czenie wy?wietlacza
	lcd_send_command( LCDC_ONOFF|LCDC_DISPLAYON );
	// przesuwanie kursora w prawo bez przesuwania zawarto?ci ekranu
	lcd_send_command( LCDC_ENTRY|LCDC_ENTRYR );

	// kasowanie ekranu
	lcd_clr();
}

void lcd_locate (uint8_t x, uint8_t  y)
{
    switch(y)
	{
		case 0: y = LCD_LINE1; break;

#if (LCD_ROWS>1)
	    case 1: y = LCD_LINE2; break; // adres 1 znaku 2 wiersza
#endif
#if (LCD_ROWS>2)
    	case 2: y = LCD_LINE3; break; // adres 1 znaku 3 wiersza
#endif
#if (LCD_ROWS>3)
    	case 3: y = LCD_LINE4; break; // adres 1 znaku 4 wiersza
#endif
	}

	lcd_send_command( (uint8_t)(0x80 + y + x) );
    
}
void lcd_clr(void)
{
   lcd_send_command( LCDC_CLS ); 
}
void lcd_char (char znak)
{
    lcd_send_data( ( znak>=0x80 && znak<=0x87 ) ? (znak & 0x07) : znak);
}
void lcd_str  (char * str)
{
   register char znak;
   while ( (znak=*(str++)) ) lcd_char( znak ); 
}
void lcd_int  (int liczba)
{
    
}