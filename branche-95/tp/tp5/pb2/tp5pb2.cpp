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
 * Nom fichier: tp5pb2.cpp
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

	// cli est une routine qui bloque toutes les interruptions.
	// Il serait bien mauvais d'être interrompu alors que
	// le microcontroleur n'est pas prêt...

	cli ();

	// configurer et choisir les ports pour les entrées
	// et les sorties. DDRx... Initialisez bien vos variables
	//Initialisation des variables
	DDRA = OUT; 
	DDRD = IN;

	// cette procédure ajuste le registre EIMSK
	// de l’ATmega324PA pour permettre les interruptions externes

	EIMSK |= (1 << INT0) ;

	// il faut sensibiliser les interruptions externes aux
	// changements de niveau du bouton-poussoir
	// en ajustant le registre EICRA

	EICRA |= (1 << ISC00) ;

	// sei permet de recevoir à nouveau des interruptions.

	sei ();

}

//////////////////////// ISR bouton poussoir
ISR (INT0_vect) {
	boutonPoussoir = 1; 

}

///////////////////// ISR minuterie expiree
ISR (TIMER1_COMPA_vect){
	minuterieExpiree = 1;
	
}


/**************************************************************************
 * Fonction clignotiLumiere()
 * Description: 
 * Return: 
 **************************************************************************/
void clignotiLumiere(){
	PORTA = ROUGE;
	_delay_ms(100);
	PORTA = ETEINT;
}


/**************************************************************************
 * Fonction boutonAppuye()
 * Description: Verifier que le bouton a ete appuye et relache completement
 * Return: vrai si bouton a ete appuye (et relache), sinon faux
 **************************************************************************/
 void partirMinuterie ( uint16_t duree ) {
	minuterieExpiree = 0;
	// mode CTC du timer 1 avec horloge divisée par 1024
	// interruption après la durée spécifiée
	TCNT1 = 0; 
	OCR1A = duree;
	TCCR1A = 0;
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
	TCCR1C = 0;
	TIMSK1 |= (1 << OCIE1A);
}
 

/***************************************************
 * Fonction main()
 **************************************************/
 
int main()
{
	initialisation();
	
	_delay_ms(10000);
	clignotiLumiere();
	partirMinuterie(7812);
	
	do {	
	}
	while (minuterieExpiree == 0 && boutonPoussoir == 0 );
	
	if(minuterieExpiree == 1) {
		PORTA = ROUGE;}
	else{
		PORTA = VERT;
	}
	
	
	
	cli();
	
	
	
	
}
