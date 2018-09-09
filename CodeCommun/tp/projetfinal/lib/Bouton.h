/**
 * NOM DE FICHIER : bouton.h
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 28 mars 2018 
 * la DEL est reliee a la pin 3 du port D
 *
 **/
 
#ifndef BOUTON_H
#define BOUTON_H
 
 
#pragma once

#include "Constantes.h"

class Bouton
{
public:

	Bouton();
		
	uint8_t statut();
};

#endif
