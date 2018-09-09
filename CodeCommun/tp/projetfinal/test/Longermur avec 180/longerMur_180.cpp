/**
 * NOM DE FICHIER : testcapteur.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * DATE DE MODIFICATION : 23 fevrier 2018 
 * 
 **/
 
using namespace std;

#include <util/delay.h>
#include <avr/io.h> 
#include "Del.h"
#include "Can.h"
#include "Moteur.h"
#include "Delais.h"
#include "Son.h"
#include "Capteur.h"


void init()
{
	DDRA = 0x00;  // PORT A est en mode Entree    
	DDRB = 0xff;  // PORT B est en mode sortie
	DDRC = 0xff;  // PORT C est en mode sortie
}

//Gauche pour le test, après je vais la généraliser
void ajustement(uint8_t &sortie, Capteur &capteur, Moteur &moteur)
{
	// On longe la gauche
	bool coteLonger=false;

	if (!coteLonger){
		while(sortie !=15 && sortie<60) {
			valeurmoyenne(sortie,capteur);
			if(sortie > 15 ) {
				moteur.ajustementMoteur(50,25,1,1);
				_delay_ms(500);
				valeurmoyenne(sortie,capteur);
			}
			else if(sortie < 15) {
				moteur.ajustementMoteur(25,50,1,1);
				_delay_ms(500);
				valeurmoyenne(sortie,capteur);
			}
		}	
	}
	
}
//Sort la moyenne de 10 lectures
void valeurmoyenne(uint8_t &sortie, Capteur &capteur){
	uint8_t total=0;
	for (uint8_t i=0;i<10;i++){
		total+=capteur.detectionCm();
	}
	sortie = (total*0.1)+0.5;
}

int main()
{
	can convertisseur; 
	can* conv = &convertisseur;
	Del led;
	Son piezo(60);
	Capteur capteurGauche(conv,0,15,0);
	Capteur capteurDroit(conv,1,15,1);

	Moteur moteur;
	moteur.init();
	// Entre 14 et 16 cm, on n'ajuste pas
	for(;;)
	{
	while((sortieCapteurGauche>13) && (sortieCapteurGauche<17)) { 
		moteur.avancer();
		led.allumerVert();
		valeurmoyenne(sortieCapteurGauche,capteurGauche);
	}

	while((sortieCapteurGauche<=13) | (sortieCapteurGauche>=17)) {
		led.allumerRouge();
		// Fin de mur potentiel
		if(sortieCapteurGauche > 60){
			_delay_ms(100);
			valeurmoyenne(sortieCapteurGauche,capteurGauche);
			// Confirmation fin de mur, Début du tour
			if(sortieCapteurGauche > 60){
				moteur.arretMoteur();
				piezo.start();
				_delay_ms(500);
				piezo.stop();
				moteur.avancer();
				//---------------------------------------------------------
				_delay_ms(2000); //attend de depasser le bord completement
				moteur.gauche90();//tourne de 90 degre
				moteur.avancer();
				_delay_ms(1000);//attend de depasser le mur au complet
				//---------------------------------------------------------
				valeurmoyenne(sortieCapteurGauche,capteurGauche);
				// Si c'etait un mur et non un angle, on fait un 90 de plus
				if(sortieCapteurGauche > 60){
					//----------------------------------------------------------
					moteur.gauche90();//tourne de 90 degre
					moteur.avancer();
					_delay_ms(500);//reviens au mur
					//----------------------------------------------------------
					valeurmoyenne(sortieCapteurGauche,capteurGauche);
				}
				}
			}
		
		else {
			ajustement(sortieCapteurGauche,capteurGauche,moteur);
		}
	}
	
	}
	return 0;
}
		
	
	
	
