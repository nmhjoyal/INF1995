
using namespace std;

#include <util/delay.h>
#include <avr/io.h> 

#define ENABLE 0
#define DIR 1

const uint8_t MOTEUR_ON = (1 << ENABLE);
const uint8_t AVANCER = (1 << DIR);

/************************************
* La fonction eteint le moteur
**************************************/
void eteindreMoteur() { PORTC &= ~MOTEUR_ON; }

/*************************************************
* La fonction allume le moteur
*************************************************/
void allumerMoteur() { PORTC |= MOTEUR_ON; }

/************************************************
* La fonction permet d'avoir un delais variable en effectuant n fois un delais de 1ms
************************************************/
void delaisVariable1Ms(int n)
{
	for (int i = 0; i < n; i++) // applique n fois un delais de 1ms
	{
		_delay_ms(1); 
	}
}

/************************************************
* La fonction permet d'avoir un delais variable en effectuant n fois un delais de 10us
************************************************/
void delaisVariable10Us(int n)
{
	for (int i = 0; i < n; i++) // applique n fois un delais de 10us
	{
		_delay_us(10); 
	}
}

/************************************************
* La fonction permet de faire tourner le moteur a 60 Hz pendant 2s
* avec un ratio a sur b determine par le parametre ratioab
************************************************/
void moteur60Hz(int ratioab)
{
	int b = 16; //la periode du signal correspond a 1/frequence ce qui donne 16ms
	int a = 16*ratioab/100;
	for (int i = 0; i < 125; i++) // applique 125 le cycle de 16ms ce qui dure 2s
	{
		allumerMoteur();
		delaisVariable1Ms(a);
		eteindreMoteur();
		delaisVariable1Ms(b-a);
	}
}

/************************************************
* La fonction permet de faire tourner le moteur a 400 Hz pendant 2s
* avec un ratio a sur b determine par le parametre ratioab
************************************************/
void moteur400Hz(int ratioab)
{
	int b = 250; //la periode du signal correspond a 1/frequence ce qui donne 2500us
				 //cependant comme nous travaillerons avec des delais de 10us cela donne 250*10us 
	int a = 250*ratioab/100;
	for (int i = 0; i < 800; i++) // applique 800 le cycle de 2500us ce qui dure 2s
	{
		allumerMoteur();
		delaisVariable10Us(a);
		eteindreMoteur();
		delaisVariable10Us(b-a);
	}
}



int main() {

	DDRC = 0xff;  // PORT C est en mode sortie

	moteur60Hz(0);
	moteur60Hz(25);
	moteur60Hz(50);
	moteur60Hz(75);
	moteur60Hz(100);
	
	moteur400Hz(0);
	moteur400Hz(25);
	moteur400Hz(50);
	moteur400Hz(75);
	moteur400Hz(100);

}
