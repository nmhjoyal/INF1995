/**
 * NOM DE FICHIER : Capteur.h
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 4 avril 2018 
 * 
 **/
 
#pragma once 
 
#include "Del.h"
#include "Can.h"

using namespace std;


class Capteur{
	public:
	
		Capteur();
		//Constructeur par param
		Capteur(can*, uint8_t pin, uint8_t cote);
		
		//Destructeur
		~Capteur();
		
		//getters
		uint8_t getPin();

		//detecte s'il y a un obstacle et à quelle distance il est
		uint8_t detection();
		uint8_t detectionCm();

		void operator=(Capteur*);
		
	private:
		can* convertisseur_;
		uint8_t pin_; //1 pour gauche et 2 pour droit	
		uint8_t cote_; // DROIT ou GAUCHE
};
