/**
* NOM DE FICHIER : communicationUART.cpp
* AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
* 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
* DATE DE MODIFICATION : 12 mars 2018
*
**/

#include "CommunicationUART.h"

/*********************************************
* Initialisation des registres pour permettre 
* la reception et la transmission du UART
**********************************************/

void CommunicationUART::initialisationUART ( void ) {

	//Initialisation des registres
	UBRR0H = 0;
	UBRR0L = 0xCF;

	UCSR0A = 0 ;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	
	UCSR0C = (1<<USBS0)|(3<<UCSZ00) ;

}

/*********************************************
* Envoi des données de la mémoire 
* dans UART
* 
* Param: (IN) donnee
* 		 Un octet transmise a l'USB
*********************************************/

void CommunicationUART::transmissionUART ( uint8_t donnee ) {
	
	while ( !( UCSR0A & (1<<UDRE0)) );
	//Put data into buffer, sends the data
	UDR0 = donnee;
}

/*********************************************
* Reception d'une donnee via l'USB
* 
* Retour: Un octet a l'entree du registre 
* 		  UDR0
*********************************************/

uint8_t CommunicationUART::receiveUART()
{
	//test s'il y a une donnee a recevoir
	while(!(UCSR0A & (1<<RXC0)));
	
	return UDR0;
}


