/**
 * NOM DE FICHIER : conversion_can_cm.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * DATE DE MODIFICATION : 9 avril 2018 
 * 
 **/
 
using namespace std;

#include <util/delay.h>
#include <avr/io.h> 
#include <math.h>
#include "del.h"
#include "can.h"

/*
fonction capteur droit:
x est la valeur CAN
y est la distance en cm
y=740,03*x^(-0.822)
-----------------------
fonction capteur gauche:
x est la valeur CAN
y est la distance en cm
y=681,06*x^(-0.765)

*/

void init()
{
	DDRA = 0x00;  // PORT A est en mode Entree    
}

uint8_t can_cm_droit (uint8_t valeurcan){

	return 740.03*pow(valeurcan,-0.822);
}

uint8_t can_cm_gauche (uint8_t valeurcan){
	
	return 681.06*pow(valeurcan,-0.765);
}

int main()
{
	init();
	
	can convertisseur; //initialisation du convertisseur analogique-numerique
	Del led;
	
	for(;;)
	{
	
		uint8_t sortieCapteurGauche = convertisseur.lecture(0) >> 2; //nous decalons la sorie de 2 bit vers la droite afin de garder les 8 bits les plus significatifs 
		//uint8_t sortieCapteurDroit = convertisseur.lecture(5) >> 2;
		
		while(sortieCapteurGauche == 90)
			led.allumerVert();

		led.eteindre();

	}
	return 0;
	

}
		
	
	
	
