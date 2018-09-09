/**
 * NOM DE FICHIER : del.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 28 mars 2018 
 * la DEL est reliee aux pins 1 et 2 du Port B 
 *
 **/
 
#include "Del.h"


/************************************
 * Le constructeur met les pins 1 et 2 du port b en sortie
 ************************************/
Del::Del()
{
	DDRB |= 0x03;
}

/************************************
 * La fonction eteint la DEL
 ************************************/
void Del::eteindre() 
{
	PORTB = ETEINT;
}

/*************************************************
 * La fonction allumerRouge allume la DEL en rouge
 *************************************************/
void Del::allumerRouge() 
{
	PORTB = ROUGE;
}


/************************************************
 * La fonction allumerVert allume la DEL en vert
 ************************************************/
void Del::allumerVert() 
{
	PORTB = VERT;
}

/**************************************************
 * La fonction allumerAmbre allume la DEL ambre
 * pour un duree en millisecondes
 * Param: (IN) dureeMS 
 **************************************************/
void Del::allumerAmbre(uint16_t dureeMS) 
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

void Del::clignoterLumiere(uint8_t COULEUR){

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
