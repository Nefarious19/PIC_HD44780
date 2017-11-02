
#include <xc.h>
#include <stdint.h>
#include "common.h"

#include "itoa.h"

char * itoa (int number, char * buffer)
{
    char * wsk = buffer;
    int number_len = 0;
    int temp_num = number;
    if(number < 0)
    {
        * wsk++ = '-';
        number = number * (-1);
    }
    
    
    do
    {
        number_len++;
    }
    while( (temp_num /= 10) );
    
    wsk = wsk + number_len - 1;
    temp_num = number;
    
    while(number_len)
    {
      *wsk-- =  (char)((temp_num%10)+'0');
      temp_num = temp_num / 10;
      number_len--;
    }  
    
    return buffer;
}