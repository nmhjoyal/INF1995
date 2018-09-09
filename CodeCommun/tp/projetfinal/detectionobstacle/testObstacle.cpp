/**
* NOM DE FICHIER : detectionObstacle.cpp
* AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
* 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
* DATE DE MODIFICATION : 12 mars 2018
**/


#include "Robot.h"

volatile uint8_t cote = 0;
volatile uint8_t mesure[5];
//volatile uint8_t i = 0; //deplacement dans le tableau distance
//enum etat {rien, mur, poteau}

const uint8_t rien = 0;
const uint8_t mur = 1;
const uint8_t poteau = 2;

volatile uint8_t etatDetection = rien;
uint8_t obstacle[3]; 

/**************************************************
 * Part la minuterie avec duree ou 8000000/1024 = 1 seconde
 **************************************************/
/*void partirMinuterie ( uint16_t duree ) 
{
	TCNT1 = 0; 
	OCR1A = duree;
	TCCR1A = 0;
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
	TCCR1C = 0;
	TIMSK1 |= (1 << OCIE1A);
}
*/
/**************************************************
 * Interruption si la minuterie est expiree
 **************************************************/
/*ISR ( TIMER1_COMPA_vect ) 
{	
	can convert;
	if (cote == DROIT)
		mesure[i] = convert.lecture(1);
	else if(cote == GAUCHE)
		mesure[i] = convert.lecture(2);
	i++;
	if (i != 5)
		partirMinuterie(8000000/1024/2); //(0.5 seconde)
	else
		i =0;
		//detecter si poteau...
}
*/
uint8_t trouverObstacle(Robot& frobie){
	for (uint8_t i =0 ; i<= 2; i++){ //recolte 3 donnée pour savoir si c'est un mur ou un poteau
		obstacle[i] = frobie.detectionObstacle();
		frobie.allumerDel();
		_delay_ms(150);
		frobie.eteindreDel();
		_delay_ms(150); //delais entre chaque detection A DETERMINER
		
	}
				
	if ((obstacle[0] - obstacle[1]) <= 3 && (obstacle[0] - obstacle[2]) > 5)
		return poteau;
	else if ((obstacle[0] - obstacle[1]) <= 3 && (obstacle[0] - obstacle[2]) <= 5)
		return mur;
	else 
		return rien;
}

int main(){
	
	can convertisseur;
	
	Capteur capteurdroit(&convertisseur, 1, DROIT);
	Capteur capteurgauche(&convertisseur, 2, GAUCHE);
	Robot frobie;
	uint8_t distance= 0;
	uint8_t distance1 = 0;
	uint8_t distance2 = 0;
	uint8_t ok = false;
	
	/*while (!ok){
		//Décide de quel cote le robot commence à longer
		if (capteurdroit.detectionCm() <= 20){
			cote = DROIT;
			frobie = Robot(&capteurgauche, &capteurdroit, DROIT);
			ok = true;
		}
		else if (capteurgauche.detectionCm() <= 20){
			cote = GAUCHE;
			frobie = Robot(&capteurdroit, &capteurgauche, GAUCHE);
			ok = true;
		}
	}*/
	
	cote = DROIT;
	frobie = Robot(&capteurgauche, &capteurdroit, DROIT);
	
	for (;;){
		/*frobie.longerMur();*/
		frobie.avancer();
		
		distance = frobie.detectionObstacle();
		
		if (distance > 60){
			distance1 = 0;
			distance2 = 0;
			etatDetection = rien;
			frobie.setPeutChanger(true);
		}
		else{	
			switch (etatDetection){	
			case rien : //si on detecte qqch alors qu'avant on ne detectais rien
				etatDetection = trouverObstacle(frobie);
				if (etatDetection == poteau)
					frobie.signalPoteau();
				else if (etatDetection == mur){
					//doit changer de mur car on vient de passer un vide et l'objet detecte est un mur
					distance2 = obstacle[0];
					distance1 = obstacle[1];
					distance = obstacle[2];
					/*frobie.changerMur();
					frobie.longerMur();
					//apres sort du switchcase et recommence à longer et détecter avec le for(;;)
			*/
					}
				break;
			
			case mur: 
				distance2 = distance1; //les deux dernières données de distance
				distance1 = distance;
				if ((distance1 - distance2) > 5){ //si la différence entre les deux donnée est de plus de 10 cm
					etatDetection = trouverObstacle(frobie);
					if (etatDetection == poteau)
					frobie.signalPoteau();
				}
				break;
			
			}//fin switch
		}//fin else
	}//fin for(;;)
}//fin main







