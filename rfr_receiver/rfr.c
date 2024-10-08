6///////rx


#include<avr/io.h>
#include<stdio.h>
#include<usart.h>
#include<initialise_16.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<bitwise.h>


#define PD1 read_adc(0)
#define PD2 read_adc(1)
#define PD3 read_adc(2)
#define PD4 read_adc(3)
#define PD5 read_adc(4)
#define PD6 read_adc(5)
#define PD7 read_adc(6)
#define PD8 read_adc(7)

#define L_OCR OCR1AL
#define R_OCR OCR1BL


/*************GLOBAL VARIABLES********/


enum motor_type 				{ml    ,	 pumpr   ,pumpl ,mr};
enum led 				{led1,led2,led3,led4,led5,led6,led7,led8};
//VALUES===>>>						0		   1	

unsigned char *motor_port_a[]=	{&PORTC, &PORTC ,   &PORTC,&PORTD}; 
unsigned char motor_pin_a[]=	{	  2,	   5,      0,		 6};

unsigned char *motor_port_en[]=	{&PORTC, &PORTC ,   &PORTC,&PORTD};
unsigned char motor_pin_en[]=	{	  4,	   7,     1 ,		 4};

unsigned char *motor_port_b[]=	{&PORTC, &PORTC ,   &PORTD,&PORTD};
unsigned char motor_pin_b[]=	{	  3,	   6,     7 ,		 5};

unsigned char rotate_a[]={0,1,0,1};
unsigned char rotate_b[]={0,0,1,1};

unsigned char *led_port[]={&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB,&PORTB};
unsigned char led_pin[]={0,1,2,3,4,5,6,7};
unsigned char sens[8],sensor,n=0,x=0,i;





/**********FUNCTIONS***********/

void move_motor(char motor,char dir)
	{

		change_bit(motor_port_a[motor],motor_pin_a[motor],rotate_a[dir]);
		change_bit(motor_port_b[motor],motor_pin_b[motor],rotate_b[dir]);

	}
	
	
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
void bot_forward(void)
{
move_motor(ml,forward);
move_motor(mr,forward);
}
void bot_reverse(void)
{
move_motor(ml,reverse);
move_motor(mr,reverse);
}

void bot_brake(void)
{
move_motor(ml,brake);
move_motor(mr,brake);
}
void bot_rad_right(void)
{
move_motor(ml,forward);
move_motor(mr,brake);
}
void bot_rad_right_b(void)
{
move_motor(ml,reverse);
move_motor(mr,brake);
}
void bot_rad_left(void)
{
move_motor(ml,brake);
move_motor(mr,forward);
}
void bot_rad_left_b(void)
{
move_motor(ml,brake);
move_motor(mr,reverse);
}
void bot_diff_right(void)
{
move_motor(ml,forward);
move_motor(mr,reverse);
}
void bot_diff_left(void)
{
move_motor(ml,reverse);
move_motor(mr,forward);
}
void pump_on()
{
move_motor(pumpr,forward);
}

void pump_off()
{
move_motor(pumpr,brake);
}

void buzzer_on()
{
DDRD=0xFF;
change_bit(&PORTD,3,1);
}

void buzzer_off()
{DDRD=0xF7;
change_bit(&PORTD,3,0);
}

void autonomous()
{
	bot_brake();
	PORTB=0xFF;
	L_OCR=100;
	R_OCR=100;
	
	
	while( PD1>128&&PD2>128&&PD3>128&&PD4>128&&PD5>128&&PD6>128&&PD7>128&&PD8>128 )
		{	scanf("%c",&i);
			if(i=='r')
			main();
		
		}
	PORTB=0x00;


	while(1)
	{
		scanf("%c",&i);
			if(i=='r')
			main();
			
		if(PD3<128)
		{

			PORTB=0x00;
			change_bit(&PORTB,2,1);
			bot_forward();
			_delay_ms(200);
			bot_brake();
			buzzer_off();
			pump_on();
			_delay_ms(2000);
			pump_off();

		}
		else if(PD2<128)
		{
			PORTB=0x00;
			change_bit(&PORTB,1,1);
			bot_forward();
			_delay_ms(200);
			bot_brake();
			buzzer_off();
			pump_on();
			_delay_ms(2000);
			pump_off();
		}
		else if(PD1<128)
		{
			PORTB=0x00;
			change_bit(&PORTB,0,1);
			bot_diff_right();
			while(PD2>128);
			change_bit(&PORTB,1,1);
			bot_brake();
			buzzer_off();
			pump_on();
			_delay_ms(2000);
			pump_off();
		}
		else if(PD8<128)
		{	PORTB=0x00;
			change_bit(&PORTB,7,1);
			bot_diff_right();
			while(PD2>128);
			change_bit(&PORTB,1,1);
			bot_brake();
			buzzer_off();
			pump_on();
			_delay_ms(2000);
			pump_off();
		}//


		else if(PD4<128)
		{
			PORTB=0x00;
			change_bit(&PORTB,3,1);
			bot_diff_left();
			while(PD3>128);
			change_bit(&PORTB,2,1);
			bot_brake();
			buzzer_off();
			pump_on();
			_delay_ms(2000);
			pump_off();		
		}
		else if(PD5<128)
		{
			PORTB=0x00;
			change_bit(&PORTB,4,1);
			bot_diff_left();
			while(PD3>128);
			change_bit(&PORTB,2,1);
			bot_brake();
			buzzer_off();
			pump_on();
			_delay_ms(2000);
			pump_off();
		}
		else if(PD6<128)
		{PORTB=0x00;
			change_bit(&PORTB,5,1);
			bot_diff_left();
			while(PD3>128);
			change_bit(&PORTB,2,1);
			bot_brake();
			buzzer_off();
			pump_on();
			_delay_ms(2000);
			pump_off();
		}

		else if(PD7<128)
		{PORTB=0x00;
			change_bit(&PORTB,6,1);
			bot_diff_right();
			while(PD2>128);
			change_bit(&PORTB,1,1);
			bot_brake();
			buzzer_off();
			pump_on();
			_delay_ms(2000);
			pump_off();
		}

		buzzer_off();
	}//wh ends 



}
int main(void)////////////rx
{
unsigned char ii=0;


 init_port();
 init_usart();
 init_adc();
sei();
 
 char i;
 while(1)
	{

	scanf("%c",&ii);
	_delay_ms(10);
	switch(ii)
	{

		PORTB=0;

		case 'a':
			PORTB=0x00;
			bot_forward();
			
			change_bit(&PORTB,1,1);
			change_bit(&PORTB,2,1);
			break;

		case 'b':
			PORTB=0x00;
			bot_reverse();
			
			change_bit(&PORTB,5,1);
			change_bit(&PORTB,6,1);
			break;

		case 'd':
			PORTB=0x00;
			bot_diff_left();
			
			
			change_bit(&PORTB,4,1);
			break;

		case 'e':
			PORTB=0x00;
			bot_diff_right();//left forward
			
			change_bit(&PORTB,0,1);
			break;
			
		case 'm':
			PORTB=0x00;
		    bot_rad_right();
			change_bit(&PORTB,1,1);
			change_bit(&PORTB,2,1);
			break;
			
		case 'q':
			PORTB=0x00;
		    bot_rad_left();
			change_bit(&PORTB,1,1);
			change_bit(&PORTB,2,1);
			break;	
		case 'n':
			PORTB=0x00;
		    bot_rad_right_b();
			change_bit(&PORTB,1,1);
			change_bit(&PORTB,2,1);
			break;
		case 'p':
			PORTB=0x00;
		    bot_rad_left_b();
			change_bit(&PORTB,1,1);
			change_bit(&PORTB,2,1);
			break;
		case 'h'://auto mode
			autonomous();
			break;


		case 'g':
			pump_on();
			break;

		case 'j'://led testing
		ii=0;
		unsigned char i;
		while(1)
		{ scanf("%c",&i);
			if(i=='r')
			main();
		  
			change_bit(&PORTB,ii%8,1);
			_delay_ms(100);
			change_bit(&PORTB,ii%8,0);
			_delay_ms(100);
			ii++;
			
		}
		
		break;
		
		
		case 'r':    //reset
			main();
			break;
		default:
			bot_brake();
			pump_off();
			PORTB=0xaa;
			break;


		}//sw

	}//wh
return 0;
}