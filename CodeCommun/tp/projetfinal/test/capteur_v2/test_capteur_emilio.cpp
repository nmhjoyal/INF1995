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
#include "moteur.h"

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
	DDRC = 0xff;  // PORT C est en mode sortie
	can convertisseur; //initialisation du convertisseur analogique-numerique
	del led;
	Moteur moteur;
	bool surMurDroit = false; 
	bool surMurGauche = false;
	bool objetADroite=false;
	bool objetAGauche=false;
	bool droitDeChanger = true;
	moteur.arretMoteur();
	led.eteindre();
	for(;;)
	{
		
		//1ere Etape
		
		/** nous utilisons la pin 1 du port A pour le capteur gauche, donc ADC0, l'argument de lecture est donc 0 
		    nous utilisons la pin 6 du port A pour le capteur gauche, donc ADC0, l'argument de lecture est donc 5
		    sortie = (V/5)*255 avec V le voltage correspondant 
		    a la distance entre le mur et le capteur 
		    Voir V dans la documentation du capteur **/
		
		uint8_t sortieCapteurGauche = convertisseur.lecture(0) >> 2; //nous decalons la sorie de 2 bit vers la droite afin de garder les 8 bits les plus significatifs 
		uint8_t sortieCapteurDroit = convertisseur.lecture(5) >> 2;

		void checkcotes(){

			//28 équivaut à 60cm (valeur approx)
			if (sortieCapteurGauche>28){
				objetAGauche=true;
			}
			else objetAGauche=false;
			
			if (sortieCapteurDroit>28){
				objetADroite=true;
			}
			else objetADroite=false;
			// Coté initial
			// 92 (droit) et 95 (gauche) équivalent à 15cm pour capteurDroit et capteurGauche
			if (!surMurDroit & !surMurGauche){
				if (sortieCapteurGauche<96 & sortieCapteurGauche > 94){
					surMurGauche=true;
				}

				if (sortieCapteurDroit<93 & sortieCapteurDroit > 91){
					surMurDroit=true;
				}
			}
		}

		while (surMurGauche){

			while(sortieCapteurGauche == 95) { //Allumer la del en rouge quand le capteur est a 15cms du mur. 95 => 1.86V
			led.allumerRouge();
			moteur.avancer();
			sortieCapteurGauche = convertisseur.lecture(0) >> 2; 
			}
		
			while(sortieCapteurGauche != 95) {
				led.eteindre();
				sortieCapteurGauche = convertisseur.lecture(0) >> 2;

				if(sortie < 95) {
					moteur.ajustementMoteur(50,25,1,1);
				}
				else {
					moteur.ajustementMoteur(25,50,1,1);
				}
			}
		}

		while (surMurDroit){

			while(sortieCapteurDroit == 92) { //Allumer la del en rouge quand le capteur est a 15cms du mur. 95 => 1.86V
			led.allumerRouge();
			moteur.avancer();
			sortieCapteurDroit = convertisseur.lecture(5) >> 2; 
			}
		
			while(sortieCapteurDroit != 92) {
				led.eteindre();
				sortieCapteurDroit = convertisseur.lecture(5) >> 2;

				if(sortie < 92) {
					moteur.ajustementMoteur(25,50,1,1);
				}
				else {
					moteur.ajustementMoteur(50,25,1,1);
				}
			}
		}
		
		/**while(sortieCapteurGauche == 95) { //Allumer la del en rouge quand le capteur est a 15cms du mur. 95 => 1.86V
			led.allumerRouge();
			moteur.avancer();
			sortie = convertisseur.lecture(0) >> 2; 
		}
		
		while(sortieCapteurGauche != 95) {
			led.eteindre();
			sortieCapteurGauche = convertisseur.lecture(0) >> 2;
			if(sortie < 95) {
				moteur.ajustementMoteur(25,50,1,1);
			}
			else {
				moteur.ajustementMoteur(50,25,1,1);
			}
		}**/
	}
	return 0;
}
		
	
	
	
