/**
 * NOM DE FICHIER : main.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 14 mars 2018 
 * test de la librairie
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
	while(!(UCSR0A & (1<<RXC0)))
	{};
	
	return UDR0;
}

int main()
{
	DDRD = ENTREE;
	DDRB = SORTIE;
	DDRA = SORTIE; 
	
	del led;
	communicationUART uart;
	Memoire24CXXX memoire;

	uart.initialisationUART();
	
	clignoterLumiere(led, rouge);
	_delay_ms(350);
	clignoterLumiere(led, vert);	
	
	//lecture des 2 premiers octets du fichier (contiennent la taille du fichier)
	uint8_t premierTaille = USART_Receive();
	uint8_t deuxiemeTaille = USART_Receive();
//	uint16_t nombreInstruction = (((premierTaille << 8) + deuxiemeTaille)-2)/2;
	
	//pour chaque commande, enregistrer en memoire l'instruction et l'operande
	for(uint16_t i = 1; i <= NOMBRE_INSTRUCTIONS; i++)
	{
		uint8_t instruction = USART_Receive();
		uint8_t operande = USART_Receive();
		memoire.ecriture(i*16, &instruction, sizeof(instruction));
		memoire.ecriture(i*16+8, &operande, sizeof(operande));
		
	}
}
