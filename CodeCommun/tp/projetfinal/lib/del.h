/**
 * NOM DE FICHIER : del.h
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 28 mars 2018 
 * la DEL est reliee aux pins 1 et 2 du Port B 
 *
 **/
 
#ifndef DEL_H
#define DEL_H

#include "Constantes.h"

class Del
{
public:

	Del();
		
	void eteindre();
	void allumerRouge();
	void allumerVert();
	void allumerAmbre(uint16_t dureeMS);
	void clignoterLumiere(uint8_t COULEUR);
	
private:
};

#endif
