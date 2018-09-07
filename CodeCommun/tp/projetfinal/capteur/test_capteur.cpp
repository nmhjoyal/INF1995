/**
 * NOM DE FICHIER : testcapteur.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * DATE DE MODIFICATION : 23 fevrier 2018 
 * 
 **/
 
using namespace std;

#include <util/delay.h>
#include <avr/io.h> 
#include "../lib/can.h"
#include "../lib/del.cpp"

/**
 * Un petit test pour s'assurer du bon fonctionnement du capteur avec
 * le convertisseur CAN. La DEL s'allume en rouge quand le capteur est 
 * a 15cms d'un mur 
 * 
 **/


int main()
{
	DDRA = 0x00;  // PORT A est en mode Entree    
	DDRB = 0xff;  // PORT B est en mode sortie
	can convertisseur; //initialisation du convertisseur analogique-numerique
	del led;
	
	for(;;)
	{
		//nous utilisons la pin 1 du port a, donc ADC0, l'argument de lecture est donc 0 
		uint8_t sortie = convertisseur.lecture(0) >> 2; //nous decalons la sorie de 2 bit vers la droite afin de garder les 8 bits les plus significatifs 
		
		
		/** sortie = (V/5)*255 avec V le voltage correspondant 
		 * a la distance entre le mur et le capteur 
		 * Voir V dans la documentation du capteur **/
		
		if (sortie == 95)  //Allumer la del en rouge quand le capteur est a 15cms du mur. 95 => 1.86V
			led.allumerRouge();
		else 
			led.eteindre();
	}
	return 0;
}
		
	
	
	
