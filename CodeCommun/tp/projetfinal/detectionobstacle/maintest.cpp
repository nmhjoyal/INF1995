/**
* NOM DE FICHIER : detectionObstacle.cpp
* AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
* 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
* DATE DE MODIFICATION : 12 mars 2018
**/


#include "Robot.h"
/*
volatile uint8_t cote = 0;
volatile uint8_t obstacle[5];
volatile uint8_t i = 0; //deplacement dans le tableau distance
enum etat = {rien, debut, mur, poteau};

/**************************************************
 * Interruption si la minuterie est expiree
 **************************************************/
/*ISR ( TIMER1_COMPA_vect ) 
{	
	can convert();
	if (cote == droit)
		osbtacle[i] = convert.lecture(1);
	else if(cote == gauche)
		obstacle[i] = convert.lecture(2);
	i = i + 1;
	if (i != 5)
	partirMinuterie(0.5);
}
*/

/**************************************************
 * Part la minuterie avec duree en seconde
 **************************************************/
/*void partirMinuterie ( uint16_t duree ) 
{
	minuterieExpiree = 0;
	
	TCNT1 = 0; 
	OCR1A = duree;
	TCCR1A = 0;
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
	TCCR1C = 0;
	TIMSK1 |= (1 << OCIE1A);
}
*/

int maint(){
	
	enum stadeDetection = {rien, mur};
	stadeDetection etat = rien;
	//droit = 0 et gauche = 1
	
	
	can convertisseur;
	
	Capteur capteurdroit(&convertisseur, 1, distanceideal, droit);
	Capteur capteurgauche(&convertisseur, 2, distanceideal, gauche);
	
/**************************************************
 * Décide de quel cote le robot commence à longer
 **************************************************/
	if (capteurdroit.detectionCm <= 20){
			cote = droit;
			frobie Robot(&capteurgauche, &capteurdroit,  droit, 1);
	}
	else if (capteurgauche.detectionCm <= 20){
			cote = gauche;
			frobie Robot(&capteurdroit, &capteurgauche,  gauche, 1);
	}
	
	for (;;){
		
		frobie.longerMur();
		
		/***************************************************
		* La fonction détecte s'il y a un poteaux, un mur ou 
		* rien du côté du capteurdétection et agit en conséquence
		****************************************************/
		distance = frobie.detectionObstacle();
		
		if (distance >= 60){
			distance1 = 0;
			distance2 = 0;
			etat = rien;
			frobie.setPeutChanger(1);
		}
		else{	
		switch (etat){	
			case(rien){ //si on detecte qqch alors qu'avant on ne detectais rien
				for (uint8_t i =0 ; i<= 5; i++){ //recolte 5 donnée pour savoir si c'est un mur ou un poteau
					obstacle[i] = frobie.detectionObstacle();
					_delay_ms(0.1); //delais entre chaque detection A DETERMINER
					}
				
				if ((obstacle[0] - obstacle[4]) > 8){ //8 étant le minimum pouvant représenter 10 cm
					//implémentation pour les son et lumière de detection de poteau
					}
				else if{//doit changer de mur car on vient de passer un vide et l'objet detecte est un mur
					frobie.changerMur();
					frobie.longerMur();
					//apres sort du switchcase et recommence à longer et détecter avec le for(;;)
					
					}
				
			}
				
			case (mur){
				distance2 = distance1; //les deux dernières données de distance
				distance1 = distance;
				if ((distance1 - distance2)> 8){ //si la différence entre les deux donnée est de plus de 10 cm
					for (uint8_t i =0 ; i<= 2; i++){ //recolte 3 données pour savoir si c'est un mur ou un poteau
					obstacle[i] = frobie.detectionObstacle();
					_delay_ms(0.3); //delais entre chaque detection A DETERMINER
					}
				
					if ((obstacle[0] - obstacle[2]) > 8){ //8 étant le minimum pouvant représenter 10 cm
					//implémentation pour les son et lumière de detection de poteau
					}
					else{//le nouvel objet detecte est un mur
					}//verifie 
				}
			}//fin case mur
			
		}//fin switch
			
		}//fin else
	}//fin for(;;)
}//fin main







