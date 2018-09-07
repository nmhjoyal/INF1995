
using namespace std;

#include <util/delay.h>
#include <avr/io.h> 

const uint8_t ROUGE = (1 << 1);
const uint8_t VERT = (1 << 0);
const uint8_t ETEINT = (1 << 0) & (1 << 1);


/************************************
* La fonction eteindre eteint la DEL
************************************/
void eteindre() { PORTB = ETEINT; }

/*************************************************
* La fonction allumerRouge allume la DEL en rouge
*************************************************/
void allumerRouge() { PORTB = ROUGE; }

/************************************************
* La fonction allumerRouge allume la DEL en vert
************************************************/
void allumerVert() { PORTB = VERT; }

/************************************************
* La fonction permet d'avoir un delais variable en effectuant n fois un delais de 10 us
************************************************/
void delaisVariable(int n)
{
	for (int i = 0; i < n; i++) // applique n fois un delais de 10 us
	{
		_delay_us(10); 
	}
}

/************************************************
* La fonction éteint la DEL rouge en 3 seconde
************************************************/
void eteindreLedRougeEn3s()
{
	int ratioab = 1.0; //ratio a sur b
	for (int i = 0; i < 3000; i++) // 3s correspond a 3000 cycle de 1ms
	{
		ratioab = 100 - (i / 30); //diminue le ratio a sur b a chaque cycle
		allumerRouge();
		delaisVariable(ratioab);
		eteindre();
		delaisVariable((100 - ratioab));
	}
}

/************************************************
* La fonction éteint la DEL verte en 3 seconde
************************************************/
void eteindreLedVerteEn3s()
{
	int ratioab = 1.0; //ratio a sur b
	for (int i = 0; i < 3000; i++) // 3s correspond a 3000 cycle de 1ms
	{
		ratioab = 100 - (i / 30); //diminue le ratio a sur b a chaque cycle
		allumerVert();
		delaisVariable(ratioab);
		eteindre();
		delaisVariable((100 - ratioab));
	}
}

int main() {

	DDRB = 0xff;  // PORT B est en mode sortie

	for(;;)
	{
		allumerRouge();
		eteindreLedRougeEn3s();
		_delay_ms(1000);

		allumerVert();
		eteindreLedVerteEn3s();
		_delay_ms(1000);
	}
}
