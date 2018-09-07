 /**
 * NOM DE FICHIER : TP5_Ex1.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * DATE DE MODIFICATION : 7 fevrier 2018 
 **/
 

#include <util/delay.h>
#include <avr/io.h> 
#include <avr/interrupt.h>

const uint8_t ROUGE = (1<<1);
const uint8_t VERT = (1<<0);
const uint8_t ETEINT = (1<<0) & (1<<1);
volatile uint8_t etat = 0;
volatile uint8_t etatBouton;

/**************************************************
 * Interruption si le bouton est enfoncé ou relaché
 **************************************************/
ISR ( INT0_vect ) 
{
	_delay_ms(30); // laisser un delai de 30 ms (anti-rebond)

	if (etatBouton != (PIND & 0x04))
	{
		etatBouton = PIND & 0x04;
		if(etat < 5)
			etat ++;
		else
			etat = 0;
	}
	EIFR |= (1 << INTF0); // Remet le flag a 0
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
	// genere une interruption quand le bouton change d'état
	EICRA |= (1 << ISC00); 

	sei (); // réactive les interruptions.
}

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

/********************************************************************************
 * La fonction allumerAmbre appelle en alternance allumerRouge() et allumerVert() 
 * avec un delais de 5 ms
 ********************************************************************************/
void allumerAmbre()
{ 
	allumerRouge();
	_delay_ms(5);  
	allumerVert();
	_delay_ms(5);  
}


int main()
{
	initialisation();
	etatBouton = PIND & 0x04;
	// Enumeration des etats
	enum etats { Init , Ambre , Vert1 , Rouge , Eteint , Vert2 }; 

	for(;;)  // boucle sans fin
	{  
		switch (etat)
		{
			case Init:
				allumerRouge();
				break;
				
			case Ambre:
				allumerAmbre();
				break;
                
			case Vert1:
				allumerVert(); 
				break;
                
			case Rouge:
				allumerRouge();
				break;

			case Eteint:
				eteindre();
				break;
                
			case Vert2:
				allumerVert();
				break;
			
			default:
				break;
		}
	}
	return 0;     
}  
   
