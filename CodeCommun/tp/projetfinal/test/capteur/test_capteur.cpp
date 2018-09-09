/**
 * NOM DE FICHIER : testcapteur.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * DATE DE MODIFICATION : 23 fevrier 2018 
 * 
 **/
 
using namespace std;

#include <util/delay.h>
#include <avr/io.h>
#include "Robot.h"

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

/*void ajustementCapteurDroit(can &convertisseur, uint8_t & sortie, Moteur &moteur)
{
	while(!(sortie < 94 && sortie > 92)) {
		sortie = convertisseur.lecture(5) >> 2;
		if(sortie < 92) {
			moteur.ajustementMoteur(50,25,1,1);
		}
		else if(sortie > 94) {
			moteur.ajustementMoteur(25,50,1,1);
		}

	}
}

void ajustementCapteurGauche(can &convertisseur, uint8_t & sortie, Moteur &moteur)
{
	while(!(sortie < 96 && sortie > 94)) {
		sortie = convertisseur.lecture(0) >> 2;
		if(sortie < 94) {
			moteur.ajustementMoteur(25,50,1,1);
		}
		else if(sortie > 96) {
			moteur.ajustementMoteur(50,25,1,1);
		}
	}
}*/




int main()
{
	
	
	can convertisseur; //initialisation du convertisseur analogique-numerique
	
	Capteur capteurGauche(&convertisseur,1,GAUCHE);
	Capteur capteurDroit(&convertisseur,2,DROIT);
	
	Robot frobie(&capteurDroit, &capteurGauche, GAUCHE);
	
	
	frobie.getMoteur().avancer();
	frobie.changerMur();
	for(;;) {
	frobie.longerMur();
	}
	
	return 0;
}


		
	
	
	
