/*
 * Nom fichier: tp7pb1.cpp
 * Auteurs: Nicole Joyal, Emilio Gagnon, Jerome Desilets
 * Date: 28 fevrier 2018
 * Description: Probleme 1 du tp7
 */

/**************************************************************************
 * Connexions
 * DEL: PORTB[1,2]
 * Interrupt: PORTD[3]
 **************************************************************************/


#define F_CPU 8000000

#include <avr/interrupt.h>
#include <avr/io.h> 
#include <util/delay.h>


const uint8_t ROUGE = 1;
const uint8_t  VERT = (1<<1);
const uint8_t  ETEINT = 0;
const uint8_t  MAX_COMPTEUR = 120;


const uint8_t IN = 0x00;
const uint8_t OUT = 0xff;

volatile uint8_t compteur = 0;
volatile bool boutonPoussoir = false; 

/**************************************************************************
 * Fonction init()
 * Description: Initialiser ports IN/OUT et 'interrupt'
 **************************************************************************/
void init(){

	cli ();

	//Initialisation des ports
	
	DDRB = OUT; 
	DDRD = IN;

	//Permettre les interruptions externes

	EIMSK |= (1 << INT0) ;

	//Sensibiliser les interruptions externes aux
	//changements de niveau du bouton-poussoir

	EICRA |= (1 << ISC00) ;

	sei ();
	
}

/**************************************************************************
 * ISR()
 * Description: Procedure d'interruption, change la variable globale 
 * si bouton est appuyé
 **************************************************************************/
ISR (INT0_vect) {
	
	//Laisser un delai avant de confirmer la réponse du
	//bouton-poussoir: environ 30 ms (anti-rebond)

	_delay_ms(30);

	if(!(PIND & (1 << 2))) {
		boutonPoussoir = true;			
	}
	else {
		boutonPoussoir = false;
	}

}

/**************************************************************************
 * Fonction patternLumiere()
 * Description: Faire clignoter DEL
 **************************************************************************/
void patternLumiere(){

	//Faire clignoter vert pendant 1/2 seconde
	for(int i = 0; i < 5; i++){
		PORTB = VERT;
		_delay_ms(50);
		PORTB = ETEINT;
		_delay_ms(50);
	}
	_delay_ms(2000);
	
	//Faire clignoter compteur/2 fois rouge 2 fois par seconde
	for(int i = 0; i < compteur/2; i++){
		PORTB = ROUGE;
		_delay_ms(250);
		PORTB = ETEINT;
		_delay_ms(250);
	}	

	//Allumer vert pendant 1 seconde
	PORTB = VERT;
	_delay_ms(1000);

	//Réinitialiser 
	PORTB = ETEINT;
	compteur = 0;
}

/***************************************************
 * Fonction main()
 **************************************************/
int main()
{
	init();

	for(;;){

		compteur = 0;

		//Tant que boutonPoussoir = vrai ET compteur < 120,
		//on incrémente compteur à chaque dixième de seconde 
		while(boutonPoussoir && compteur < MAX_COMPTEUR){
			_delay_ms(100);
			compteur++;
		} 
		
		if (compteur != 0) {
			patternLumiere();
		}
	}
}
