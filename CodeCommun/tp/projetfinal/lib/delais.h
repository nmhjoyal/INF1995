/**
 * NOM DE FICHIER : delais.h
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 12 mars 2018 
 * la DEL est relie aux pins 1 et 2 du Port B 
 *
 **/

#include "constantes.h"

namespace libProjet
{
	class delais {
	public:
		void delaisVariableUs(uint8_t n);
		void delaisVariableMs(uint8_t n);
	};
}
