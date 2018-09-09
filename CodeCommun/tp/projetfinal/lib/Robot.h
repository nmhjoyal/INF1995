/**
* NOM DE FICHIER : robot.h
* AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
* 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
* DATE DE MODIFICATION : 12 mars 2018
**/

#ifndef ROBOT_H
#define ROBOT_H

#pragma once

#include "Constantes.h"
#include "Capteur.h"
#include "Moteur.h"
#include "Bouton.h"
#include "Del.h"
#include "Son.h"

class Robot
{
public:

	//Constructeur par defaut
	Robot();
	
	//Constructeur par parametres
	Robot(Capteur* detection, Capteur* mur, uint8_t cote);
	
	//getters
	uint8_t getCote();
	uint8_t getPeutChanger();
	Moteur getMoteur();
	
	//setter
	void setPeutChanger(uint8_t peutChanger);
	
	//methodes capteurs + moteur
	void changerCote();
	void changerMur();
	void longerMur();
	uint8_t detectionObstacle();
	void avancer();
	void signalPoteau();
	void allumerDel();
	void eteindreDel();
	
	
private:
	//capteur qui detecte les objets 
	Capteur *capteurDetection_;
	//capteur qui capte le mur pour le longer 
	Capteur *capteurMur_;
	
	Moteur moteur_;
	Del del_;
	Son son_;
	
	//indique si le robot longe actuellement le cote DROIT ou GAUCHE
	uint8_t cote_; 
	uint8_t peutChanger_; 
	
};

#endif //ROBOT_H
