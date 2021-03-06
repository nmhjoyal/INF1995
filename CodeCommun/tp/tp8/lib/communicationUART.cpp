/**
* NOM DE FICHIER : communicationUART.cpp
* AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
* 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
* DATE DE MODIFICATION : 12 mars 2018
*
**/

#include "communicationUART.h"

using namespace libProjet;

/************************************
* Initialisation des registres pour permettre 
* la reception et la transmission du UART
************************************/

void communicationUART::initialisationUART ( void ) {

	//Initialisation des registres
	UBRR0H = 0;
	UBRR0L = 0xCF;

	UCSR0A = 0 ;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0) ;
	
	UCSR0C = (3<<UCSZ00) ;

}

/************************************
* Envoi des données de la mémoire 
* dans UART
************************************/

void communicationUART::transmissionUART ( uint8_t donnee ) {
	
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = donnee;
}


