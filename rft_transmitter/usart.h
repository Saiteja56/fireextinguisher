#include<stdio.h>

//----uncomment eihter one if using 128-------

//#define USART_0 	//use either 1 code yet to b modified
//#define USART_1		

static void uart_baud(void)
{
	#define BAUD 1200
	#include <util/setbaud.h>
	
	#if defined (__AVR_ATmega8__)
		UBRRH = UBRRH_VALUE;
		UBRRL = UBRRL_VALUE;
		#if USE_2X
		UCSRA |= (1 << U2X);
		#else
		UCSRA &= ~(1 << U2X);
		#endif
   
   
   #elif defined (__AVR_ATmega16__)
		UBRRH = UBRRH_VALUE;
		UBRRL = UBRRL_VALUE;
		#if USE_2X
		UCSRA |= (1 << U2X);
		#else
		UCSRA &= ~(1 << U2X);
		#endif
   
	#elif defined (__AVR_ATmega128__)
		#if defined USART_0
			UBRR0H = UBRRH_VALUE;
			UBRR0L = UBRRL_VALUE;
			#if USE_2X
			UCSR0A |= (1 << U2X);
			#else
			UCSR0A &= ~(1 << U2X);
			#endif
		#endif
		
		#if defined USART_1
			UBRR1H = UBRRH_VALUE;
			UBRR1L = UBRRL_VALUE;
			#if USE_2X
			UCSR1A |= (1 << U2X);
			#else
			UCSR1A &= ~(1 << U2X);
			#endif
		#endif
	#endif
	
}




int uart_putchar(char c, FILE *unused)
{
	

  #if defined (__AVR_ATmega8__)
		if (c == '\n')
			uart_putchar('\r', unused);
		loop_until_bit_is_set(UCSRA, UDRE);
		UDR = c;
		return 0;
		
     #elif defined (__AVR_ATmega16__)
		if (c == '\n')
			uart_putchar('\r', unused);
		loop_until_bit_is_set(UCSRA, UDRE);
		UDR = c;
		return 0;
		
	
	#elif defined (__AVR_ATmega128__)
		
		#if defined USART_0
			if (c == '\n')
				uart_putchar('\r', unused);
			loop_until_bit_is_set(UCSR0A, UDRE);
			UDR0 = c;
			return 0;
		#endif
		
		#if defined USART_1
			if (c == '\n')
				uart_putchar('\r', unused);
			loop_until_bit_is_set(UCSR1A, UDRE);
			UDR1 = c;
			return 0;
		#endif
	#endif
	
}

char uart_getchar(FILE *unused)
{
	#if defined (__AVR_ATmega8__)
	
		// Wait until a byte has been received 
		while((UCSRA&(1<<RXC)) == 0) ; 
		// Return received data 
		return UDR;
		
		#elif defined (__AVR_ATmega16__)
	
		// Wait until a byte has been received 
		while((UCSRA&(1<<RXC)) == 0) ; 
		// Return received data 
		return UDR; 
		
	
	#elif defined (__AVR_ATmega128__)
		
		#if defined USART_0
			// Wait until a byte has been received 
			while((UCSR0A&(1<<RXC)) == 0) ; 
			// Return received data 
			return UDR0;
		#endif
	
		#if defined USART_1
			// Wait until a byte has been received 
			while((UCSR1A&(1<<RXC)) == 0) ; 
			// Return received data 
			return UDR1;
		#endif
		
	#endif
	//will be problamatic if using both usart in 128
}


static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,_FDEV_SETUP_WRITE);
static FILE mystdin = FDEV_SETUP_STREAM(NULL,uart_getchar,_FDEV_SETUP_READ);



/*   SAMPLE USAGE

#include<avr/io.h>
#include<usart.h>
#include<initialise_16.h>

unsigned char a,i=3;
int main(void)
{

    init_usart();
	
	while(1)
	{
		scanf("%c",&a);
		printf("%c",a);
	}
	return 0;
} */

