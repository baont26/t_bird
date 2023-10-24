#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
void led_init();
void led_put(uint8_t led);
void timer_3();
void init_interrupt_timer3_ctc();

uint8_t current_led_state=0x00;
unsigned int counter=0;

int main(void)
{
	led_init();
	timer_3();
	led_put(0xF0);
	while (1)
	{
	}
}
//1s
ISR(TIMER3_COMPA_vect)
{
	
	counter+=1;
	if(counter==1)
	{
		counter=0;
		current_led_state=current_led_state^0x0F;
		led_put(current_led_state);
	}
}


void timer_3()
{
	
	const uint8_t mode_ctc=(0<<WGM31)|(0<<WGM30);
	const uint8_t pres_256=(1<<CS32)|(0<<CS31)|(0<<CS30);
	
	TCCR3A|= (0<<COM3A1) | (0<<COM3A0) | (0<<COM3B1) | (0<<COM3B0) |(0<<COM3C1) | (0<<COM3C0) | mode_ctc;
	TCCR3B|= (0<<ICNC3) | (0<<ICES3) | (0<<0) | ( 0<<WGM33) | (1<<WGM32) |pres_256;
	TCCR3C = 0x00;
	
	OCR3AH = 0x7A; // Tong OCR3A = 31249
	OCR3AL = 0x11;
	
	init_interrupt_timer3_ctc();
}

void init_interrupt_timer3_ctc()
{
	ETIMSK |=(1<<OCIE3A); //| (1<<OCIE3B) ;
	sei();
}

void led_init()
{
	DDRB=0xF0;
	DDRD=0xF0;
}

void led_put(uint8_t led)
{
	PORTB=led << 4;
	PORTD=led;
}
