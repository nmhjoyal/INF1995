//TABLEAU D'ETATS
/********************************
*   EP  *  A  *  ES    *   Z    *
*********************************
* ETAT0 *  0  * ETAT0  * ROUGE  *
* ETAT0 *  1  * ETAT1  * ROUGE  * 
* ETAT1 *  0  * ETAT2  * ORANGE *
* ETAT1 *  1  * ETAT1  * ORANGE *
* ETAT2 *  0  * ETAT2  * VERT   *   
* ETAT2 *  1  * ETAT3  * VERT   *
* ETAT3 *  0  * ETAT4  * ROUGE  *
* ETAT3 *  1  * ETAT3  * ROUGE  *
* ETAT4 *  0  * ETAT4  * ETEINT *
* ETAT4 *  1  * ETAT5  * ETEINT *
* ETAT5 *  1  * ETAT5  * VERT   *
* ETAT5 *  0  * ETAT0  * VERT   *
*********************************/
//LEGENDE: EP=Etat Present; ES= Etat suivant;
// A = entree (bouton); Z= sortie (del)

/*
 * Nom fichier: tp5pb3.cpp
 * Auteurs: Nicole Joyal, Emilio Gagnon, Jerome Desilets
 * Date: 9 fevrier 2018
 * Description: Ceci est le probleme 2 du tp5
 */

/**************************************************************************
 * Connexions
 * DEL: PORTA[1,2]
 **************************************************************************/
#define F_CPU 8000000
#include <avr/interrupt.h>
#include <avr/io.h> 
#include <util/delay.h>
const uint8_t ROUGE = (1<<0);
const uint8_t  VERT = (1<<1);
const uint8_t  ETEINT = (1<<0)&(1<<1);
volatile uint8_t ETAT = 0;
volatile bool appuye = 0;
const int IN = 0x00;
const int OUT = 0xff;

volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir; 

/**************************************************************************
 * Fonction 
 * Description: 
 * Return: 
 **************************************************************************/
// placer le bon type de signal d'interruption
// à prendre en charge en argument

void initialisation ( void ) {

	

}

void ajustementPWM ( uint8_t freqA, uint8_t freqB ) {
	// mise à un des sorties OC1A et OC1B sur comparaison
	// réussie en mode PWM 8 bits, phase correcte
	// et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
	// page 177 de la description technique du ATmega324PA)

	OCR1A = freqA*255/100;
	OCR1B = freqB*255/100;

}
 

/***************************************************
 * Fonction main()
 **************************************************/
 
int main()
{
	DDRD = OUT;
	TCCR1A |= (1 << WGM10) | (1<<COM1A1) | (1<<COM1B1);
	TCCR1B |= _BV(CS11) ;
	TCCR1C = 0;
	
	for(;;){
		
		ajustementPWM(100,100);
		_delay_ms(2000);
		ajustementPWM(75,75);
		_delay_ms(2000);
		ajustementPWM(50,50);
		_delay_ms(2000);
		ajustementPWM(25,25);
		_delay_ms(2000);
		ajustementPWM(0,0);
		_delay_ms(2000);
	}
	
	
}
