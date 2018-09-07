/**
* NOM DE FICHIER : pwm.h
* AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
* 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
* DATE DE MODIFICATION : 12 mars 2018
* la DEL est reliee aux pins 1 et 2 du Port B
*
**/

#pragma once
#include "constantes.h"


namespace libProjet
{
	class pwm
	{
		public:

			void ajustementPWM(uint8_t droite, uint8_t gauche, uint8_t directionGauche, uint8_t directionDroite);
			void arretMoteur();

	};

}