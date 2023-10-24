#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
void led_init();
void led_put(uint8_t led);
void timer_3();
void init_interrupt_timer3_nor();

uint8_t current_led_state=0x00;
unsigned int counter=0;



int main(void)
{
	led_init();
	//Timer0_init();
	timer_3();
    led_put(0xF0);
	while (1)
	{
	}
}

ISR(TIMER3_OVF_vect){
	
	TCNT3H=0x0B;
	TCNT3L=0xDC;
	counter+=1;
	if(counter==1){
		counter=0;
		current_led_state=current_led_state^0x0F;
		led_put(current_led_state);
	}
}



void timer_3()
{
	const uint8_t mode_nor=(0<<WGM31)|(0<<WGM30);
	const uint8_t pres_256=(1<<CS32)|(0<<CS31)|(0<<CS30);
	
	TCCR3A|= (0<<COM3A1) | (0<<COM3A0) | (0<<COM3B1) | (0<<COM3B0) |(0<<COM3C1) | (0<<COM3C0) | mode_nor;
	TCCR3B|= (0<<ICNC3) | (0<<ICES3) | (0<<0) | ( 0<<WGM33) | (0<<WGM32) |pres_256;

	TCCR3C =0x00;
	
	TCNT3H=0x0B;
	TCNT3L=0xDC;
	
	
	init_interrupt_timer3_nor();
}

void init_interrupt_timer3_nor()
{
	ETIMSK|=1<<TOIE3;
	sei();
}


void led_init(){
	DDRB=0xF0;
	DDRD=0xF0;
}

void led_put(uint8_t led){
	PORTB=led << 4;
	PORTD=led;
}
