#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
void led_init();
void led_put(uint8_t led);
void timer_1();
void init_interrupt_timer1_nor();

uint8_t current_led_state=0x00;
unsigned int counter=0;

int main(void)
{
	led_init();
	timer_1();
    led_put(0xF0);
	while (1)
	{
	}
}
//1s
ISR(TIMER1_COMPA_vect)
{
	
	counter+=1;
	if(counter==1)
	{
		counter=0;
		current_led_state=current_led_state^0x0F;
		led_put(current_led_state);
	}
}


void timer_1()
{
	
	const uint8_t mode_ctc=(0<<WGM11)|(0<<WGM10);
	const uint8_t pres_256=(1<<CS12)|(0<<CS11)|(0<<CS10);
	
	TCCR1A|= (0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) |(0<<COM1C1) | (0<<COM1C0) | mode_ctc;
	TCCR1B|= (0<<ICNC1) | (0<<ICES1) | (0<<0) | ( 0<<WGM13) | (1<<WGM12) |pres_256;
    TCCR1C = 0x00;
	
	OCR1AH = 0x7A; // Tong OCR1A = 31249
	OCR1AL = 0x11;
	
	init_interrupt_timer1_nor();
}

void init_interrupt_timer1_nor()
{
	TIMSK |=(1<<OCIE1A); //| (1<<OCIE1B) ;
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
