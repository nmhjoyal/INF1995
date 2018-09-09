/**
* NOM DE FICHIER : communicationUART.h
* AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
* 			Nicole Joyal, Emilio Gagnon, Jérôme Désilets
* DATE DE MODIFICATION : 12 mars 2018
*
**/

#ifndef COMMUNICATIONUART_H
#define COMMUNICATIONUART_H


#pragma once


#include "Constantes.h"

class CommunicationUART
{
public:
	
	void initialisationUART(void);

	void transmissionUART(uint8_t donnee);
	uint8_t receiveUART();
};

#endif



