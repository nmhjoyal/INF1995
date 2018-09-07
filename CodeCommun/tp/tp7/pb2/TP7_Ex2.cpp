/**
 * NOM DE FICHIER : TP7_Ex2.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * DATE DE MODIFICATION : 23 fevrier 2018 
 * 
 * la DEL est relie aux pins 1 et 2 du Port B 
 * la photorésistance est relie a la pin 1 du Port A
 **/
 
using namespace std;

#include <util/delay.h>
#include <avr/io.h> 
#include "can.h"

const uint8_t ROUGE = (1<<1);
const uint8_t VERT = (1<<0);
const uint8_t ETEINT = (1<<0) & (1<<1);
volatile uint8_t compteur = 0;

/************************************
 * La fonction eteindre eteint la DEL
 ************************************/
void eteindre() 
{
	PORTB = ETEINT;
}

/*************************************************
 * La fonction allumerRouge allume la DEL en rouge
 *************************************************/
void allumerRouge() 
{
	PORTB = ROUGE;
}

/************************************************
 * La fonction allumerRouge allume la DEL en vert
 ************************************************/
void allumerVert() 
{
	PORTB = VERT;
}

/********************************************************************************
 * La fonction allumerAmbre appelle en alternance allumerRouge() et allumerVert() 
 * avec un delais de 5 ms
 ********************************************************************************/
void allumerAmbre()
{
	allumerRouge ();
	_delay_ms(5);  
	allumerVert ();
	_delay_ms(5);     
}

int main()
{
	DDRA = 0x00;  // PORT A est en mode Entree    
	DDRB = 0xff;  // PORT B est en mode sortie
	can convertisseur; //initialisation du convertisseur analogique-numerique
	
	for(;;)
	{
		//nous utilisons la pin 1 du port a, donc ADC0, l'argument de lecture est donc 0 
		uint8_t sortie = convertisseur.lecture(0) >> 2; //nous decalons la sorie de 2 bit vers la droite afin de garder les 8 bits les plus significatifs 
		
		if(sortie < 150) // si l'eclairage est faible
			allumerVert();
		if(sortie > 150 && sortie < 230) // si l'eclairage est modere
			allumerAmbre();
		if(sortie > 230) // si l'eclairage est fort
			allumerRouge();
	}
	return 0;
}
		
	
	
	
