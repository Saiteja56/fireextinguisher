#include<stdio.h>
#define forward 1
#define reverse 2
#define stop 0
#define brake 3
#define ADC_VREF_TYPE 0x60
//#define ADC_VREF_TYPE 0x20


void init_port(void)
{
    //DDRA=0X00;
	//PORTA=0Xff;
	
	DDRB=0x00;   //1-pullup
	PORTB=0xff;  //0-tristate
	
	DDRC=0x00;
	PORTC=0xff;
	
	DDRD=0x02;
	PORTD=0xff;
}

void init_analog_com(void)
{
	ACSR=0x80;
	SFIOR=0x00;
}

void init_usart(void)
{
/*
// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud rate: 19200

UCSRA=0x00;
UCSRB=0x18;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x1A;
*/
/*
// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: Off
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 19200
UCSRA=0x00;
UCSRB=0x08;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x19;
*/


// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: Off
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 1200
UCSRA=0x00;
UCSRB=0x08;
UCSRC=0x86;
UBRRH=0x01;
UBRRL=0xA0;	

/*
// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: Off
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 9600
UCSRA=0x00;
UCSRB=0x08;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x33;
*/

	//UCSRA |= (1 << U2X)|(1<<MPCM);
		
	//uart_baud();//inittialises UBBRH,UBBRL,U2X
	//Serial Initialization
	UCSRB |= (1<<TXEN)| (1<<RXEN);
	//UCSRB |= (1 << RXCIE )|(1<<TXCIE)|(1 << UDRIE)|(1<<RXEN)|(1 << TXEN)|(1<<UCSZ2)|(1 << RXB8)|(1<<TXB8);
	UCSRC |= (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	//UCSRC |= (1 << URSEL )|(1<<UMSEL)|(1 << UPM1)|(1<<UPM0)|(1 << USBS)|(1<<UCSZ1)|(1 << UCSZ0)|(1<<UCPOL);
	
	stdin = &mystdin;
	stdout= &mystdout;



	/*%d - signed decimal 
    %u - unsigned decimal 
    %x - hexidecimal ("0x" is prefixed) 
    %s - string 
    use "l", e.g. %lx if the value is a 32-bit number */

}

void init_ext_interrupt(void)
{
	//GICR|=0x00;
	//MCUCR=0x00;
	//MCUCSR=0x00;
	//GIFR=0x00;
}

void init_timer_counter_interrupt(void)
{
    TIMSK=0x00;//TIMSK=(1<<OCIE2)|(1<<TOIE2)|(1<<TICIE1)|(1<<OCIE1A)|(1<<OCIE1B)|(1<<TOIE1)|(1<<OCIE0)|(1<<TOIE0);
}

void init_timer0(void)
{
	TCCR0=0x00;
	TCNT0=00;
	
}

void init_timer1(void)
{
	TCCR1A=0x00;
	TCCR1B=0x00;
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x00;
	OCR1AL=0x00;
	OCR1BH=0x00;
	OCR1BL=0x00;
}

void init_timer2(void)
{
	ASSR=0x00;
	TCCR2=0x00;
	TCNT2=0x00;
	OCR2=0x00;
}

void init_spi_slave(void)
{
	SPCR=0x00;
	SPSR=0x00;
}

void init_2wire(void)
{
	TWSR=0x00;
	TWBR=0x00;
	TWAR=0x00;
	TWCR=0x00;
}


void init_adc()
{
	ADMUX=ADC_VREF_TYPE & 0xff;
    ADCSRA=0x83;
}