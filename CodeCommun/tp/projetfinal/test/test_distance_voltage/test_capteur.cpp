/**
 * NOM DE FICHIER : testcapteur.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * DATE DE MODIFICATION : 23 fevrier 2018 
 * 
 **/
 
using namespace std;

#include <util/delay.h>
#include <avr/io.h> 
#include "del.h"
#include "can.h"

/**
 * Un petit test pour s'assurer du bon fonctionnement du capteur avec
 * le convertisseur CAN. La DEL s'allume en rouge quand le capteur est 
 * a 15cms d'un mur 
 * 
 **/

void init()
{
	DDRA = 0x00;  // PORT A est en mode Entree    
	DDRB = 0xff;  // PORT B est en mode sortie
	DDRC = 0xff;  // PORT C est en mode sortie
}


int main()
{
	init();
	
	can convertisseur; //initialisation du convertisseur analogique-numerique
	Del led;
	led.eteindre();
	
	for(;;)
	{
	
		uint8_t sortieCapteurGauche = convertisseur.lecture(0) >> 2; //nous decalons la sorie de 2 bit vers la droite afin de garder les 8 bits les plus significatifs 
		uint8_t sortieCapteurDroit = convertisseur.lecture(5) >> 2;
		
		while(sortieCapteurGauche = 90)
			led.allumerVert();

		led.eteindre();

	/*	while(sortieCapteurDroit < 94 && sortieCapteurDroit > 92)
			led.allumerRouge();

		led.eteindre();

		
	}

	*/

	return 0;

}
		
	
	
	
