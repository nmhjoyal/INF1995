/**
* NOM DE FICHIER : moteur.h
* AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
* 			 Nicole Joyal, Emilio Gagnon, J�r�me D�silets
* DATE DE MODIFICATION : 12 mars 2018
* CONNEXIONS: Moteur droit : JAUNE: D5, ORANGE: D7 
*			  Moteur gauche: JAUNE: D6, ORANGE: D8
**/

#ifndef MOTEUR_H
#define MOTEUR_H

#pragma once

#include "Constantes.h"


class Moteur
{
public:
	Moteur();
	
	void init();
	void ajustementMoteur(uint8_t gauche, uint8_t droite, uint8_t directionGauche, uint8_t directionDroite);
	void ajustementRoueDroite(uint8_t droite);
	void ajustementRoueGauche(uint8_t gauche);
	void arretMoteur();
	void avancer();
	void reculer();
	void droite180();
	void gauche180();
	void gauche90();
	void droite90();
	void droite45();
	void gauche45();
	void autourGauche180();
	void autourDroite180();
	void changerSigne(uint8_t& droite);

};

#endif //MOTEUR_H
