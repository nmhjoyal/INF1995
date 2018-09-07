/*
 * Nom fichier: tp6pb1.cpp
 * Auteurs: Nicole Joyal, Emilio Gagnon, Jerome Desilets
 * Date: 14 fevrier 2018
 * Description: Ceci est le probleme 1 du tp6
 */

/**************************************************************************
 * Connexions
 * DEL: PORTA[1,2]
 **************************************************************************/


#define F_CPU 8000000

#include <avr/io.h> 
#include <util/delay.h>
#include "memoire_24.h"
#include <string.h>


const uint8_t ROUGE = (1<<0);
const uint8_t  VERT = (1<<1);
const uint8_t  ETEINT = (1<<0)&(1<<1);

const int IN = 0x00;
const int OUT = 0xff;

/**************************************************************************
 * Fonction init()
 * Description: Initialiser
 **************************************************************************/
 
void init(){
	DDRA = OUT; 
	DDRD = IN;
}

/**************************************************************************
 * Fonction initialisationUART()
 * Description: Comparer duhhhhhh
 * Retour: vrai ou faux...
 **************************************************************************/

void initialisationUART ( void ) {
	// 2400 bauds. Nous vous donnons la valeur des deux
	// premier registres pour vous éviter des complications
	UBRR0H = 0;
	UBRR0L = 0xCF;
	// permettre la reception et la transmission par le UART0
	UCSR0A = 0;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	// Format des trames: 8 bits, 1 stop bits, none parity
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);

}

/**************************************************************************
 * Fonction transmissionUART()
 * Description: transmettre
 * Retour: vrai ou faux...
 **************************************************************************/

// De l'USART vers le PC

void transmissionUART ( uint8_t donnee ) {
 /* Wait for empty transmit buffer */
   while( !( UCSR0A & (1<<UDRE0)));
   /* Copy 9th bit to TXB8 */
   UCSR0B &= ~(1<<TXB80);
   if ( donnee & 0x0100 ){
		UCSR0B |= (1<<TXB80);
	}
   /* Put data into buffer, sends the data */
   UDR0 = donnee;

}




/***************************************************
 * Fonction main()
 **************************************************/
 
int main()
{
		initialisationUART();
	
	    char mots[21] = "bangity god\n";

		uint8_t i, j;
		
		_delay_ms(5000);
		
		for ( i = 0; i < 100; i++ ) {
			for ( j=0; j < 20; j++ ) {
				transmissionUART(mots[j]);
		}

}
}
