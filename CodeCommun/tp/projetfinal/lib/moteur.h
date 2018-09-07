/**
* NOM DE FICHIER : moteur.h
* AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
* 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
* DATE DE MODIFICATION : 12 mars 2018
* CONNEXIONS: Moteur droit : JAUNE: D5, ORANGE: D7 
*			  Moteur gauche: JAUNE: D6, ORANGE: D8
**/

#pragma once
#include "constantes.h"


class Moteur
{
public:
	Moteur();
	
	void ajustementMoteur(uint8_t gauche, uint8_t droite, uint8_t directionGauche, uint8_t directionDroite);
	void arretMoteur();
	void avancer();
	void reculer();
	void droite180();
	void gauche180();
};

