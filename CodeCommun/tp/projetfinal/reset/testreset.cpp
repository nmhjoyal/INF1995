#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "del.h"



bool diagnostic __attribute__((section(".noinit")));


void switchEtat(){
	diagnostic = !diagnostic;
}

int main()
{ 

	Del led;

	if (diagnostic)
	{
		led.allumerRouge();
		switchEtat();
		for(;;){}
	}
	else if (!diagnostic)
	{
		led.allumerVert();
		switchEtat();
		for(;;){}
	}


}
