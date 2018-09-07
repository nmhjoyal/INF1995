/*
 * Nom fichier: tp7pb2.cpp
 * Auteurs: Emilio Gagnon, Nicole Joyal, Jerome Desilets
 * Date: 28 fevrier 2018
 * Description: Ceci est le probleme 2 du tp7
 */

/**************************************************************************
 * Connexions
 * DEL: PORTB[1,2]
 **************************************************************************/


#define F_CPU 8000000

#include <avr/interrupt.h>
#include <avr/io.h> 
#include <util/delay.h>
#include "can.h"


enum ECLAIRAGE { BASSE, AMBIANTE, ELEVEE }; 

const uint8_t LIMITE_BASSE = 200;
const uint8_t LIMITE_AMBIANTE = 240;

const uint8_t ROUGE = 1;
const uint8_t  VERT = (1<<1);
const uint8_t  ETEINT = 0;

const uint8_t IN = 0x00;
const uint8_t OUT = 0xff;

/**************************************************************************
 * Fonction init()
 * Description: Initialiser ports IN/OUT
 **************************************************************************/
void init(){
	DDRA = IN; 
	DDRB = OUT; 	
}

/**************************************************************************
 * Fonction luminosite()
 * Description: Déterminer la luminosité
 * Return: Niveau d'éclairage (enum)
 **************************************************************************/
ECLAIRAGE luminosite(){
	can capteur; 

	//On lit le capteur puis on décale de 2 bits pour avoir les 8 bits les plus
	//significatifs
	uint8_t niveau = capteur.lecture(0) >> 2;

	if(niveau < LIMITE_BASSE){
		return BASSE; 
	}else if(niveau < LIMITE_AMBIANTE){
		return AMBIANTE;
	}else{
		return ELEVEE;
	}
}

/**************************************************************************
 * Fonction allumerAmbre()
 * Description: Produit la lumière ambrée
 **************************************************************************/
 void allumerAmbre(){
	 PORTB = VERT;
	 _delay_ms(5);
	 PORTB = ROUGE; 
	 _delay_ms(2);
 }

/***************************************************
 * Fonction main()
 **************************************************/
int main()
{
	init();

	for(;;){

		//On lit la valeur sur le capteur et on la traite
		//selon le niveau
		ECLAIRAGE intensiteLumiere = luminosite();

		switch(intensiteLumiere){
		 case BASSE : 
		 	PORTB = VERT;
			break;
		 case AMBIANTE: 
		 	allumerAmbre();
			break;
		 case ELEVEE:
		 	PORTB = ROUGE;
			break;
		}
	}
}
