


void change_bit(unsigned char* reg,char bit_no,char val)
{
    if(val==1)
		*reg |= (1<<bit_no);
	else
	    *reg &= ~(1<<bit_no);
}

char check_bit(int* reg,char bit_no)
{
	char temp=*reg;
	temp &= (1<<bit_no);
	if(temp==0)
		return 0;
	else
		return 1;
}

unsigned char toggle(unsigned char n)
{
	if(n==0)
		return 1;
	else
		return 0;
}



/* Sample usage

#define SERVO &PORTA
#define X 6
#define Z 7

char a;

change_bit(SERVO,X,0);
change_bit(SERVO,Z,1);

//else
change_bit(&PORTA,0,0);

a=check_bit(&PORTA,6);

if((check_bit(&PORTA,3))==0)
{
}

a=toggle(a);*/
