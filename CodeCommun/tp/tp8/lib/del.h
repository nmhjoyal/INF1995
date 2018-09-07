/**
 * NOM DE FICHIER : del.h
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 2 mars 2018 
 * la DEL est reliee aux pins 1 et 2 du Port B 
 *
 **/
 
#pragma once

#include "constantes.h"

namespace libProjet
{

	class del
	{
		public:
			
			
			void eteindre();
			void allumerRouge();
			void allumerVert();
			void allumerAmbre(uint16_t dureeMS);
	
	};
}

