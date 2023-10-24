#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
void Timer0_init();
void init_interrupt_timer0_nor();
void init_interrupt_timer0_ctc();
void led_init();
void led_put(uint8_t led);
void timer_1();
void init_interrupt_timer1_nor();

uint8_t current_led_state=0x00;
unsigned int counter=0;



int main(void)
{
	led_init();
	//Timer0_init();
	timer_1();
    led_put(0xF0);
	while (1)
	{
	}
}
/*ISR(TIMER0_OVF_vect){
	
	TCNT0=131;
	counter+=1;
	if(counter==1000){
		counter=0;
		current_led_state=current_led_state^0x0F;
		//Toggle LED
		led_put(current_led_state);
	}
}*/

ISR(TIMER1_OVF_vect){
	
	//TCNT1H=0x0B;
	//TCNT1L=0xDC;
	counter+=1;
	if(counter==1){// Counter la thoi gian cua "TCNT nhan voi no" , tuc la thoi gian led nhap nhay va tat di
		counter=0;
		current_led_state=current_led_state^0x0F;
		//Toggle LED
		led_put(current_led_state);
	}
}


//dem 1 giay
/*void Timer0_init()
{
	const uint16_t mode_nor=(0<<WGM00)|(0<<WGM01);
	const uint16_t mode_pwm=(0<<WGM00)|(1<<WGM01);
	const uint16_t mode_ctc=(1<<WGM00)|(0<<WGM01);
	const uint16_t mode_fpwm=(1<<WGM00)|(1<<WGM01);
	
	const uint16_t pres_0=(0<<CS02)|(0<<CS01)|(0<<CS00);
	const uint16_t pres_1=(0<<CS02)|(0<<CS01)|(1<<CS00);
	const uint16_t pres_8=(0<<CS02)|(1<<CS01)|(0<<CS00);
	const uint16_t pres_32=(0<<CS02)|(1<<CS01)|(1<<CS00);
	const uint16_t pres_64=(1<<CS02)|(0<<CS01)|(0<<CS00);
	const uint16_t pres_128=(1<<CS02)|(0<<CS01)|(1<<CS00);
	const uint16_t pres_256=(1<<CS02)|(1<<CS01)|(0<<CS00);
	const uint16_t pres_1024=(1<<CS02)|(1<<CS01)|(1<<CS00);
	//set mode for timer 0
	
	
	TCCR0|=(0<<FOC0)|(0<<COM01)|(0<<COM00)|pres_128|mode_nor;
	
	TCNT0=131;
	// set interrupt
	init_interrupt_timer0_nor();
	
	
}*/

void timer_1()
{
	//const uint8_t mode_nor=(0<<WGM11)|(0<<WGM10);
	const uint8_t mode_ctc=(0<<WGM11)|(0<<WGM10);
	const uint8_t pres_256=(1<<CS12)|(0<<CS11)|(0<<CS10);
	
	TCCR1A|= (0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) |(0<<COM1C1) | (0<<COM1C0) | mode_ctc;
	TCCR1B|= (0<<ICNC1) | (0<<ICES1) | (0<<0) | ( 0<<WGM13) | (1<<WGM12) |pres_256;

	TCCR1C = 0x00;
	OCR1A = 124;
	//TCNT1H = 0x0B;
	//TCNT1L = 0xDC;
	
	// doi voi timer 1 thi TCNT chia ra làm TCNT1H và TCNT1L, de tính cái này thì su dung máy tính chuy?n so TCNT tính duocc tu DEC sang BIN
	init_interrupt_timer1_nor();
}

void init_interrupt_timer1_nor()
{
	TIMSK|=1<<TOIE1;
	sei();
}


/*void init_interrupt_timer0_nor(){
	TIMSK=0x01;
	sei();
}*/

void led_init(){
	DDRB=0xF0;
	DDRD=0xF0;
}

void led_put(uint8_t led){
	PORTB=led << 4;
	PORTD=led;
}
