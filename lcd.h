/* 
 * File:   lcd.h
 * Author: rafal
 *
 * Created on November 1, 2017, 1:38 PM
 */

#ifndef LCD_H
#define	LCD_H


#define LCD_ROWS 4
#define LCD_COLS 16


#define LCD_E_LAT   LATCbits.LC1
#define LCD_RW_LAT  LATCbits.LC2
#define LCD_RS_LAT  LATCbits.LC3   
#define LCD_D4_LAT  LATCbits.LC4
#define LCD_D5_LAT  LATCbits.LC5
#define LCD_D6_LAT  LATCbits.LC6
#define LCD_D7_LAT  LATCbits.LC7

#define LCD_E_PORT   PORTCbits.RC1
#define LCD_RW_PORT  PORTCbits.RC2
#define LCD_RS_PORT  PORTCbits.RC3   
#define LCD_D4_PORT  PORTCbits.RC4
#define LCD_D5_PORT  PORTCbits.RC5
#define LCD_D6_PORT  PORTCbits.RC6
#define LCD_D7_PORT  PORTCbits.RC7    
    
#define LCD_E_TRIS   TRISCbits.TRISC1
#define LCD_RW_TRIS  TRISCbits.TRISC2
#define LCD_RS_TRIS  TRISCbits.TRISC3  
#define LCD_D4_TRIS  TRISCbits.TRISC4
#define LCD_D5_TRIS  TRISCbits.TRISC5
#define LCD_D6_TRIS  TRISCbits.TRISC6
#define LCD_D7_TRIS  TRISCbits.TRISC7
    
    
#define LCD_E_SET (LCD_E_LAT = 1)
#define LCD_E_RESET (LCD_E_LAT = 0)

#define LCD_RW_SET (LCD_RW_LAT = 1)
#define LCD_RW_RESET (LCD_RW_LAT = 0)
    
#define LCD_RS_SET (LCD_RS_LAT = 1)
#define LCD_RS_RESET (LCD_RS_LAT = 0)
    
#define LCD_WRITE LCD_RW_RESET
#define LCD_READ  LCD_RW_SET

#define LCD_COMMAND LCD_RS_RESET
#define LCD_DATA    LCD_RS_SET

#define SET_E LCD_E_SET
#define CLR_E LCD_E_RESET



// definicje adresów w DDRAM dla ró?nych wy?wietlaczy
// inne s? w wy?wietlaczach 2wierszowych i w 4wierszowych
#if ( (LCD_ROWS == 4) && (LCD_COLS == 16) )
#define LCD_LINE1 0x00		// adres 1 znaku 1 wiersza
#define LCD_LINE2 0x28		// adres 1 znaku 2 wiersza
#define LCD_LINE3 0x14  	// adres 1 znaku 3 wiersza
#define LCD_LINE4 0x54  	// adres 1 znaku 4 wiersza
#else
#define LCD_LINE1 0x00		// adres 1 znaku 1 wiersza
#define LCD_LINE2 0x40		// adres 1 znaku 2 wiersza
#define LCD_LINE3 0x10  	// adres 1 znaku 3 wiersza
#define LCD_LINE4 0x50  	// adres 1 znaku 4 wiersza
#endif


// Komendy steruj?ce
#define LCDC_CLS					0x01
#define LCDC_HOME					0x02
#define LCDC_ENTRY					0x04
	#define LCDC_ENTRYR					0x02
	#define LCDC_ENTRYL					0
	#define LCDC_MOVE					0x01
#define LCDC_ONOFF					0x08
	#define LCDC_DISPLAYON				0x04
	#define LCDC_CURSORON				0x02
	#define LCDC_CURSOROFF				0
	#define LCDC_BLINKON				0x01
#define LCDC_SHIFT					0x10
	#define LCDC_SHIFTDISP				0x08
	#define LCDC_SHIFTR					0x04
	#define LCDC_SHIFTL					0
#define LCDC_FUNC					0x20
	#define LCDC_FUNC8B					0x10
	#define LCDC_FUNC4B					0
	#define LCDC_FUNC2L					0x08
	#define LCDC_FUNC1L					0
	#define LCDC_FUNC5x10				0x04
	#define LCDC_FUNC5x7				0
#define LCDC_SET_CGRAM				0x40
#define LCDC_SET_DDRAM				0x80


    
void lcd_init (void);
void lcd_locate (uint8_t x, uint8_t  y);
void lcd_clr(void);
void lcd_char (char znak);
void lcd_str  (char * str);
void lcd_int  (int liczba);


#endif	/* LCD_H */

