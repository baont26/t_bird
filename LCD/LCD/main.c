//Hien thi dong ho tren LCD
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
uint8_t ora[2]={0,0};
void lcd_dis_time();
void lcd_time_vlt();

int main(void)
{
	lcd_init();
	
	
	
	
	while (1)
	{
		lcd_time_vlt();
		lcd_dis_time();
		_delay_ms(500);
		
		
	}
}
void lcd_time_vlt()
{
	if(ora[1]==59)
		{
			ora[1]=0;
			ora[0]++;
			if(ora[0]==59)
			ora[0]=0;
			
		}
	else ora[1]++;
}
void lcd_dis_time()
{	
	lcd_cur_posi(LCD_ROW_0,4);
	char buf[3];
	if(ora[0]<10)
		lcd_write_string("0");
	lcd_write_string(itoa(ora[0],buf,10));
	lcd_write_string(":");
	if(ora[1]<10)
		lcd_write_string("0");
	lcd_write_string(itoa(ora[1],buf,10));
	
}
