/**
* NOM DE FICHIER : communicationUART.h
* AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
* 			Nicole Joyal, Emilio Gagnon, Jérôme Désilets
* DATE DE MODIFICATION : 12 mars 2018
*
**/

#pragma once

#include "constantes.h"

namespace libProjet 
{
	class communicationUART
	{
	
	public:
	
		void initialisationUART(void);

		void transmissionUART(uint8_t donnee);
		
		unsigned char USART_Receive();
	};
}




