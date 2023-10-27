#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void port_init();
void init_interrupt_timer0_nor();
void Timer0_init();
void LED_out(uint8_t ledek);
void sevseg_out(uint8_t,uint8_t);
uint8_t led=0x01,data=0;
int main(void)
{
	
	port_init();
	Timer0_init();
	
	while (1)
	{
		
		_delay_ms(300);
		if(data==9) data=0; else data++;
	}
}
ISR(TIMER0_OVF_vect)
{
	sevseg_out(0,data);
}



void port_init()
{
	DDRA=0xFF;
	DDRB=0xF0;
	DDRD=0xF0;

}
void LED_out(uint8_t ledek)
{
	PORTB=ledek<<4;
	PORTD=ledek;
}
void Timer0_init()
{
	const uint8_t mode_nor=(0<<WGM00)|(0<<WGM01);
	const uint8_t mode_pwm=(0<<WGM00)|(1<<WGM01);
	const uint8_t mode_ctc=(1<<WGM00)|(0<<WGM01);
	const uint8_t mode_fpwm=(1<<WGM00)|(1<<WGM01);
	
	const uint8_t pres_0=(0<<CS02)|(0<<CS01)|(0<<CS00);
	const uint8_t pres_1=(0<<CS02)|(0<<CS01)|(1<<CS00);
	const uint8_t pres_8=(0<<CS02)|(1<<CS01)|(0<<CS00);
	const uint8_t pres_32=(0<<CS02)|(1<<CS01)|(1<<CS00);
	const uint8_t pres_64=(1<<CS02)|(0<<CS01)|(0<<CS00);
	const uint8_t pres_128=(1<<CS02)|(0<<CS01)|(1<<CS00);
	const uint8_t pres_256=(1<<CS02)|(1<<CS01)|(0<<CS00);
	const uint8_t pres_1024=(1<<CS02)|(1<<CS01)|(1<<CS00);
	//set mode for timer 0
	
	
	TCCR0|=(0<<FOC0)|(0<<COM01)|(0<<COM00)|pres_128|mode_nor;
	
	TCNT0=131;
	// set interrupt
	init_interrupt_timer0_nor();
	
}

void init_interrupt_timer0_nor(){
	TIMSK=0x01;
	sei();
}
void sevseg_out(uint8_t sel, uint8_t data)
{
	uint8_t res=0;
	res= 1<<7|sel<<4|data;
	PORTA=res;
}




