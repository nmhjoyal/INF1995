
using namespace std;

#include <util/delay.h>
#include <avr/io.h> 
#include <avr/interrupt.h>


/************************************************
* La fonction ajuste le PMW qui fait tourner les roues du robot
************************************************/
void ajustementPWM (uint8_t droite, uint8_t gauche) 
{
	OCR1A = (uint8_t)((uint16_t)(droite)*255/100); 
	OCR1B = (uint8_t)((uint16_t)(gauche)*255/100); 
}

int main() {

	DDRD = 0xff;  // PORT D est en mode sortie
	TCCR1A |= (1<<WGM10)|(1<<COM1A1)|(1<<COM1B1); 
	TCCR1B |= _BV(CS11); 
	TCCR1C = 0;
	for(;;)
	{
		ajustementPWM(100, 100);
		_delay_ms(2000);
		ajustementPWM(75, 75);
		_delay_ms(2000);
		ajustementPWM(50, 50);
		_delay_ms(2000);
		ajustementPWM(25, 25);
		_delay_ms(2000);
		ajustementPWM(0, 0);
		_delay_ms(2000);
	}
}

