#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Del.h"
#include "Moteur.h"



bool diagnostic __attribute__((section(".noinit")));


void switchEtat(){
	diagnostic = !diagnostic;
}

int main()
{ 

	Del led;
    Moteur moteur;

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
