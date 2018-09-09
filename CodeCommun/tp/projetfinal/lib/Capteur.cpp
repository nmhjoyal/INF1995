/**
 * NOM DE FICHIER : Capteur.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 4 avril 2018 
 * 
 **/
 
#include "Capteur.h"
#include <math.h>
using namespace std;

Capteur::Capteur() {
	DDRA = ENTREE; 
	pin_= 0;
	cote_= 0;
}

Capteur::Capteur(can* can, uint8_t pin, uint8_t cote) {
	DDRA = ENTREE; 
	convertisseur_=can;
	pin_=pin;
	cote_= cote;
}
	
	
Capteur::~Capteur(){}

/***************************************************
* Fonction accesseur
* 
* Return: pin corresspondant au capteur
****************************************************/
uint8_t Capteur::getPin(){
	return pin_;
}

/***************************************************
* La fonction lit la donnee (en volts) detecte par 
* le capteur (depend de la pin_).
* On convertit ensuite cette valeur en cm en utilisant
* une fonction de regression basée sur des valeurs 
* expérimentales.
* Return: distance en cm (pin_)
****************************************************/
uint8_t Capteur::detectionCm(){

	uint8_t valeurCan=convertisseur_->lecture(pin_) >> 2;
	//Si capteur droit
	if (cote_ == DROIT){
		return (103.8976*exp(-0.03202265*valeurCan))+0.5;
	}
	//Si capteur gauche
	if (cote_ == GAUCHE) {
		return (98.5316772*exp(-0.02807055*valeurCan))+0.5;
	} 
	return 0;
}	


uint8_t Capteur::detection(){

	uint8_t valeurCan=convertisseur_->lecture(pin_-1) >> 2;
	return valeurCan;
}

void Capteur::operator=(Capteur* cap){
	pin_ = cap->pin_;
	cote_ = cap->cote_;
}

	











