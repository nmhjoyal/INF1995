/**
 * NOM DE FICHIER : del.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 28 mars 2018 
 * la DEL est reliee aux pins 1 et 2 du Port B 
 *
 **/
 
#include "del.h"

using namespace libProjet;

/************************************
 * La fonction eteint la DEL
 ************************************/

void del::eteindre() 
{
	PORTB = ETEINT;
}

/*************************************************
 * La fonction allumerRouge allume la DEL en rouge
 *************************************************/
void del::allumerRouge() 
{
	PORTB = ROUGE;
}


/************************************************
 * La fonction allumerVert allume la DEL en vert
 ************************************************/
void del::allumerVert() 
{
	PORTB = VERT;
}

/**************************************************
 * La fonction allumerAmbre allume la DEL ambre
 * pour un duree en millisecondes
 * Param: (IN) dureeMS 
 **************************************************/
void del::allumerAmbre(uint16_t dureeMS) 
{
	for(uint16_t i=0; i<(dureeMS/10); i++)
	{
		allumerVert();
		_delay_ms(5);
		allumerRouge();
		_delay_ms(5);
	}
}

/**************************************************
 * La fonction clignoterLumiere fait clignoter la DEL
 * dans une couleur definie (dure une seconde +50 
 * millisecondes
 * 
 * Param: (IN) COULEUR
 * 		  Prend une couleur definie dans constantes.h
 * 		  Soit ROUGE, VERT ou AMBRE
 * 		    
 **************************************************/

void del::clignoterLumiere(uint8_t COULEUR){

	switch (COULEUR){
		case ROUGE:
			allumerRouge();
			_delay_ms(350);
			eteindre();
			_delay_ms(350);
			allumerRouge();
			_delay_ms(350);
			eteindre();
		break;
		case VERT:
			allumerVert();
			_delay_ms(350);
			eteindre();
			_delay_ms(350);
			allumerVert();
			_delay_ms(350);
			eteindre();
		break;
		case AMBRE:
			allumerAmbre(350);
			eteindre();
			_delay_ms(350);
			allumerAmbre(350);
			eteindre();
		break;
	}

}
