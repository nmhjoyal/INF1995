 /**
 * NOM DE FICHIER : TP5_Ex1.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * DATE DE MODIFICATION : 7 fevrier 2018 
 **/
 

#include <util/delay.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include "memoire_24.h"

const uint8_t ROUGE = (1<<1);
const uint8_t VERT = (1<<0);
const uint8_t ETEINT = (1<<0) & (1<<1);
const uint16_t addresse = 0x00;
bool compare = true; 

using namespace std; 

void initialisationUART ( void ) {

// 2400 bauds. Nous vous donnons la valeur des deux premiers registres pour vous éviter des complications

	UBRR0H = 0;
	UBRR0L = 0xCF;

// permettre la reception et la transmission par le UART0

	// UCSR0A = 'modifier ici' ;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0) ;

// Format des trames: 8 bits, 1 stop bits, none parity

	UCSR0C = (3<<UCSZ00) ;

}

void transmissionUART ( uint8_t donnee ) {

while ( !( UCSR0A & (1<<UDRE0)) )
 ;
 /* Put data into buffer, sends the data */
 UDR0 = donnee;

}

int main()
{
	initialisationUART();
	_delay_ms(5000); //Pour permettre d'ecrire serieViaUSB -l dans le terminal apres le make install
	char mots[21] = "Le robot en INF1995\n";

	uint8_t i, j;

	for ( i = 0; i < 100; i++ ) {
		for ( j=0; j < 20; j++ ) {
			transmissionUART ( mots[j] );
		}	
	}
	
	return 0;     
}  

   
