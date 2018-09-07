/**
 * NOM DE FICHIER : main.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 14 mars 2018 
 * Ecriture de
 *
 **/

#include "../../tp8/lib/del.cpp"
#include "../../tp8/lib/constantes.h"
#include "../../tp8/lib/memoire_24.h"
#include "../../tp8/lib/communicationUART.h"
#include <stdio.h>


 using namespace libProjet;
/**
 * fonction main qui main function. 
 */

enum COULEUR_DEL {eteint, rouge, vert};

void init(communicationUART uart)
{
	uart.initialisationUART();
	 
	DDRB = SORTIE; //DEL
	
}


void clignoterLumiere(del led, COULEUR_DEL couleur){
	

	switch (couleur){
		case rouge:
			led.allumerRouge();
			_delay_ms(350);
			led.eteindre();
			_delay_ms(350);
			led.allumerRouge();
			_delay_ms(350);
			led.eteindre();
		break;
		case vert:
			led.allumerVert();
			_delay_ms(350);
			led.eteindre();
			_delay_ms(350);
			led.allumerVert();
			_delay_ms(350);
			led.eteindre();
		break;
	}

}

//Retourne l'octet recu par le UART 
unsigned char USART_Receive()
{
	while(!(UCSR0A & (1<<RXC0)));
	
	return UDR0;
}

int main()
{	
	del led;
	communicationUART uart;
	Memoire24CXXX memoire;
	
	init(uart);
	
	clignoterLumiere(led, rouge);
	_delay_ms(350);
	clignoterLumiere(led, vert);	
	
	//lecture des 2 premiers octets du fichier (contiennent la taille du fichier)
	uint8_t taille1 = USART_Receive();
	uint8_t taille2 = USART_Receive();
	uint16_t taille = (((uint16_t)taille1) << 8) | taille2;
		
	memoire.ecriture(0, taille1);
	memoire.ecriture(1, taille2);
	
	uint8_t instruction;
	//pour chaque commande, enregistrer en memoire l'instruction et l'operande
	for(uint16_t i = 2; i < taille; i++)
	{
		instruction = USART_Receive();
		memoire.ecriture(i, instruction);
		
	}
	
	led.allumerRouge();
	_delay_ms(6000);
	led.eteindre();
	
	//test affichage de la memoire du robot
		
	uint8_t donneeLue;
	for (uint16_t i = 0; i< taille; i++)
	{	
		memoire.lecture(i, &donneeLue);
		
		uart.transmissionUART(donneeLue);
	}
	
}
