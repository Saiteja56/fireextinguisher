#include<stdio.h>


#define forward 1
#define reverse 2
#define stop 0
#define brake 3
#define ADC_VREF_TYPE 0x60


void init_port(void)
{
    DDRA=0X00;
	PORTA=0Xff;
	
	DDRB=0xff;   //1-pullup
	PORTB=0x00;  //0-tristate
	
	DDRC=0xff;
	PORTC=0xff;
	
	DDRD=0xFE;//11111111
	PORTD=0x90;
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

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: Off
// USART Mode: Asynchronous
// USART Baud Rate: 1200
UCSRA=0x00;
UCSRB=0x10;
UCSRC=0x86;
UBRRH=0x01;
UBRRL=0xA0;


/*
// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: Off
// USART Mode: Asynchronous
// USART Baud Rate: 9600
UCSRA=0x00;
UCSRB=0x10;
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
// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x1c;//0x1F;


}

void init_timer0(void)
{// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 125.000 kHz
// Mode: Fast PWM top=FFh
// OC0 output: Disconnected
TCCR0=0x4B;
TCNT0=0x00;
OCR0=150;

	
}
/*
void init_timer1(void)
{
	// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 125.000 kHz
// Mode: Fast PWM top=00FFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: On
TCCR1A=0x01;
TCCR1B=0x0B;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=150;
OCR1BH=0x00;
OCR1BL=170;
}
*/


void init_timer1(void)
{
// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 1000.000 kHz
// Mode: Fast PWM top=00FFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: On
TCCR1A=0x01;
TCCR1B=0x0A;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=50;
OCR1BH=0x00;
OCR1BL=50;



}
void init_timer2(void)
{

	// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 125.000 kHz
// Mode: Fast PWM top=FFh
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x4C;
TCNT2=0x00;
OCR2=200;
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

#define ADC_VREF_TYPE 0x60


void init_adc(void)
{	

	// ADC initialization
	// ADC Clock frequency: 250.000 kHz
	// ADC Voltage Reference: AVCC pin
	// ADC Auto Trigger Source: ADC Stopped
	// Only the 8 most significant bits of
	// the AD conversion result are used
	ADMUX=ADC_VREF_TYPE & 0xff;
	ADCSRA=0x83;
}