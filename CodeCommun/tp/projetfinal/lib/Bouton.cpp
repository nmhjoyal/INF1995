/**
 * NOM DE FICHIER : bouton.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 28 mars 2018 
 * la DEL est reliee a la pin 3 du Port D 
 *
 **/
 
#include "Bouton.h"


/************************************
 * Le constructeur met la pin 3 du port b en entre
 ************************************/
Bouton::Bouton()
{
	DDRB &= 0xfb;
}

/************************************
 * La fonction retourne le statut du bouton (0 si enfonce, 1 si relache)
 ************************************/
uint8_t Bouton::statut()
{
	if (PIND & 0x04) 
	{ 
		return 0x00;
	} 
	return 0x01;
}

