/**
* NOM DE FICHIER : Robot.cpp
* AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
* 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
* DATE DE MODIFICATION : 28 mars 2018
*
**/


#include <avr/io.h>
#include "Robot.h"


Robot::Robot(){
	moteur_.init();
}

/********************************************************
* Initialisation des registres reliés au pwm des moteurs
* et initialisation des attributs
********************************************************/
Robot::Robot(Capteur* captDetection, Capteur* captMur, uint8_t cote) :
capteurDetection_(captDetection), capteurMur_(captMur), cote_(cote)
{
	moteur_.init();
}

/********************************************************
* Fonction accesseur cote_
* 
* Return: sur quel cote le robot longe le mur
********************************************************/
uint8_t Robot::getCote(){
	return cote_;
}

/********************************************************
* Fonction pour tester donc on peut les effacer après les tests
********************************************************/
void Robot::avancer(){
	
	moteur_.avancer();
	}
	
void Robot::allumerDel(){
	
	del_.allumerRouge();
	}	
	
void Robot::eteindreDel(){
	
	del_.eteindre();
	}
	

/********************************************************
* Fonction accesseur peutChanger_
* Return: si le robot peut changer
********************************************************/
uint8_t Robot::getPeutChanger(){
	return peutChanger_;
}

Moteur Robot::getMoteur() {
	return moteur_;
}

/********************************************************
* Fonction set peutChanger_
* Return: change la valeur de peutChanger_
********************************************************/
void Robot::setPeutChanger(uint8_t peutChanger){
	peutChanger_ = peutChanger;
}

/********************************************************
* Fonction change la valeur de cote
* si cote est droit il devient gauche et vice versa
********************************************************/
void Robot::changerCote(){
	if (cote_ == GAUCHE)
		cote_ = DROIT;
	else if (cote_ == DROIT)
		cote_ = GAUCHE;
}

/*********************************************************
* La fonction fait changer de cote le robot. Elle change le
* role de chaque capteur (capteurMur devient capteurDetection
* et vice-versa) ainsi que le cote (pour prochains changements) 
* SI changement reussi.
* 
* Return: 1 si droit de changer et changement reussi
* 		  0 sinon
**********************************************************/
void Robot::changerMur(){
	
	switch(cote_) {
		case DROIT:
			moteur_.gauche45();
			moteur_.avancer();
			while(capteurDetection_->detection() < MIN_15_GAUCHE) {
				_delay_ms(75);
			}
			del_.allumerRouge();
			break;
		
		
		case GAUCHE:
			moteur_.droite45();
			moteur_.avancer();
			while(capteurDetection_->detection() < MIN_15_DROIT) {
				_delay_ms(75);
				
			}
			del_.allumerRouge();
			break;
		}
		changerCote();
	
	//change le role des capteurs en echangeant leur adresses
	Capteur* tmp = capteurDetection_;
	capteurDetection_ = capteurMur_;
	capteurMur_ = tmp;
	
}
	
/***************************************************
* La fonction fait longer le mur au robot en détectant 
* constamment si la distance détecté est de 15 cm et 
* ajuste la direction du robot si ce n'est pas le cas
****************************************************/
void Robot::longerMur(){
	
	del_.eteindre();
	switch(cote_) {
		
		case DROIT:
		
			while((capteurMur_->detection() > MIN_15_DROIT) && (capteurMur_->detection() < MAX_15_DROIT)) { 
				del_.allumerVert();
				moteur_.avancer(); 
			}
			
			while((capteurMur_->detection() <= MIN_15_DROIT ) || capteurMur_->detection() >= MAX_15_DROIT) {
			del_.allumerRouge();
			if (capteurMur_->detection() < MIN_15_DROIT && capteurMur_->detection() > VIDE_DROIT) {
				moteur_.ajustementMoteur(85,50,1,1);
			}
			else if(capteurMur_->detection() > MAX_15_DROIT) {
				moteur_.ajustementMoteur(50,85,1,1);
			} else if( capteurMur_->detection() <= VIDE_DROIT ) {
				moteur_.avancer();
				_delay_ms(500);
				moteur_.arretMoteur();
						while(capteurMur_->detection() <= VIDE_DROIT){
							moteur_.ajustementMoteur(85,50,1,1);
							_delay_ms(200);
						}
			}
		}
			
			break;
			
		case GAUCHE:
		
			while((capteurMur_->detection() > MIN_15_GAUCHE) && (capteurMur_->detection() < MAX_15_GAUCHE)) { 
				del_.allumerVert();
				moteur_.avancer(); 
			}
			
			while((capteurMur_->detection() <= MIN_15_GAUCHE ) || capteurMur_->detection() >= MAX_15_GAUCHE) {
			del_.allumerRouge();
			if (capteurMur_->detection() < MIN_15_GAUCHE && capteurMur_->detection() > VIDE_GAUCHE) {
				moteur_.ajustementMoteur(50,85,1,1);
			}
			else if(capteurMur_->detection() > MAX_15_GAUCHE) {
				moteur_.ajustementMoteur(85,50,1,1);
			} else if( capteurMur_->detection() <= VIDE_GAUCHE ) {
				moteur_.avancer();
				_delay_ms(500);
				moteur_.arretMoteur();
						while(capteurMur_->detection() <= VIDE_GAUCHE){
							moteur_.ajustementMoteur(50,85,1,1);
							_delay_ms(200);
						}
			}
		}
		
			break;
	}
}


/***************************************************
* La fonction retourne la distance en Cm d'un objet 
* detecte du cote capteurdetection
****************************************************/
uint8_t Robot::detectionObstacle(){
	return capteurDetection_->detection();
}

/***************************************************
* fait 3 sons de 200 ms
****************************************************/
void Robot::signalPoteau()
{
	son_.signalPoteau();
}










