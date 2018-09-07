/**
 * NOM DE FICHIER : TP5_Ex2.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * DATE DE MODIFICATION : 7 fevrier 2018 
 **/
 
using namespace std;

#include <util/delay.h>
#include <avr/io.h> 
#include <avr/interrupt.h>

const uint8_t ROUGE = (1<<1);
const uint8_t VERT = (1<<0);
const uint8_t ETEINT = (1<<0) & (1<<1);
volatile uint8_t minuterieExpiree = 0;
volatile uint8_t boutonPoussoir = 0; 

/************************************
 * La fonction eteindre eteint la DEL
 ************************************/
void eteindre() {PORTB = ETEINT;}

/*************************************************
 * La fonction allumerRouge allume la DEL en rouge
 *************************************************/
void allumerRouge() {PORTB = ROUGE;}

/************************************************
 * La fonction allumerRouge allume la DEL en vert
 ************************************************/
void allumerVert() {PORTB = VERT;}


/**************************************************
 * Interruption si le bouton est enfoncé
 **************************************************/
ISR ( INT0_vect ) 
{
	boutonPoussoir = 1;
}

/**************************************************
 * Interruption si la minuterie est expiree
 **************************************************/
ISR ( TIMER1_COMPA_vect ) 
{
	minuterieExpiree = 1;
}

/**************************************************
 * Part la minuterie avec duree en seconde
 **************************************************/
void partirMinuterie ( uint16_t duree ) 
{
	minuterieExpiree = 0;
	
	TCNT1 = 0; 
	OCR1A = duree;
	TCCR1A = 0;
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
	TCCR1C = 0;
	TIMSK1 |= (1 << OCIE1A);
}



/*******************************
 * Initialisation des parametres
 ******************************/
void initialisation () 
{
	cli (); // bloque les interruptions

	DDRD = 0x00;  // PORT D est en mode Entree    
	DDRB = 0xff;  // PORT B est en mode sortie
	
	// Ajuste le registre EIMSK pour permettre les interruptions externes pour INT0
	EIMSK |= (1 << INT0); 
	// genere une interruption quand le bouton est enfoncé
	EICRA |= (1 << ISC01); 

	sei (); // réactive les interruptions.
}

int main()
{
	initialisation();
	_delay_ms(10000); //delais de 10s
	allumerRouge();
	_delay_ms(100); //allume la lumiere rouge 1/10s
	eteindre();
	partirMinuterie(8000000/1024); //part une minuterie de 1 seconde
	do {
		// attente
	} while ( minuterieExpiree == 0 && boutonPoussoir == 0 );
	
	cli ();
	
	if (minuterieExpiree == 1)
		allumerRouge();

	if (boutonPoussoir == 1)
		allumerVert();

	return 0;     
}  
