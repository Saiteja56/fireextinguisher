#include<avr/io.h>
#include<stdio.h>
#include<usart.h>
#include<initialise_16.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<bitwise.h>

/*************GLOBAL VARIABLES********/

#define ADC_VREF_TYPE 0x60

enum motor_type 				{mr    ,	 ml   ,fanl		,fanr};
enum led 						{led1,led2,led3,led4};
//VALUES===>>>						0		   1	

unsigned char *motor_port_a[]=	{&PORTC, &PORTC ,   &PORTD,&PORTC}; 
unsigned char motor_pin_a[]=	{	  3,	   5,      5,		2};

unsigned char *motor_port_en[]=	{&PORTC, &PORTC ,   &PORTD,&PORTD};
unsigned char motor_pin_en[]=	{	  4,	   7,     4 ,		3};

unsigned char *motor_port_b[]=	{&PORTD, &PORTC ,   &PORTD,&PORTC};
unsigned char motor_pin_b[]=	{	  7,	   6,     6 ,		1}	;

unsigned char rotate_a[]={0,1,0,1};
unsigned char rotate_b[]={0,0,1,1};

unsigned char *led_port[]={&PORTB,&PORTB,&PORTB,&PORTB};
unsigned char led_pin[]={0,1,2,3};
unsigned char sens[4],sensor;

unsigned char read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
_delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCH;
}

int main(void)
{
 init_port();
 init_adc();
init_usart();
 //init_timer0();
//init_timer2();
 //init_timer1();
//init_analog_com();
 //init_timer_counter_interrupt();
 sei();

 unsigned char i,POT1,POT2;


 
 

while(1)//tx
	{	
	POT1=read_adc(0);
	POT2=read_adc(1);
	
	
		
		if(check_bit(&PIND,4)==0)
		{
		i='h';				//auto
		printf("%c",i);
	
		}
		
	else 	if(check_bit(&PIND,3)==0)
		{
		i='r';				//reset
		printf("%c",i);
	
		}
		else if(check_bit(&PIND,5)==0)
		{
		i='g';				//pump_on
		printf("%c",i);
	
		}
		
		else if(check_bit(&PIND,6)==0)
		{
		i='j';				//led testing
		printf("%c",i);
	
		}
		
		else if((POT1>200 && POT2<50)||(POT1<50 && POT2>200))
		{
		if(POT1>200 && POT2<50)
		i='a';//bot forward
		
		 if(POT1<50 && POT2>200)
		i='b';//bot reverse
		}
		
		else if((POT1<50 && POT2<50)||(POT1>200 && POT2>200))
		{
		 if(POT1<50 && POT2<50)
		i='e';//bot diff right
		
		 if(POT1>200 && POT2>200)
		i='d';//bot diff left
		
		}
		
		
		else if((POT1<50 || POT1>200))
		{
		 if(POT1<50)
		i='p';//bot  right
		
		 if(POT1>200)
		i='q';//bot radial right 
		
		}
		
		else if((POT2<50 || POT2>200))
		{
		 if(POT2<50)
		i='m';//bot radial left
		
		 if(POT2>200)
		i='n';//bot diff left
		
		}
		
		else
		i='c';
	
		_delay_ms(10);
		printf("%c",i);
	}//wh
	return 0;
}