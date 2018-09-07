//TABLEAU D'ETATS
/*
 * Nom fichier: tp4pb1.cpp
 * Auteurs: Nicole Joyal, Emilio Gagnon, Jerome Desilets
 * Date: 31 janvier 2018
 * Description: Ceci est le probleme 1 du tp4
 */

/***********************************************************************
 * Connexions
 * DEL: PORTA[1,2]
 **********************************************************************/


#define F_CPU 8000000

#include <avr/io.h> 
#include <util/delay.h>

const uint8_t ROUGE = (1<<0);
const uint8_t VERT = (1<<1);
const uint8_t ETEINT = (1<<0)&(1<<1);

const int IN = 0x00;
const int OUT = 0xff;
static const int MAX = 1000; //1000 marche

/**************************************************************************
 * Fonction boucleDelai()
 * Description: Faire un delai selon la frequence
 * Parametre in: Max - nbDepart de microsecondes de delai
 **************************************************************************/
 
 void boucleDelai(int nbDepart){
	if (nbDepart >= 0){
		for(int a=nbDepart; a<MAX; a++){
			_delay_us(1);
		}
	}
 }
 
 
/***************************************************
 * Fonction main()
 **************************************************/
 
int main()
{
	//Initialisation des variables
	DDRA = OUT; 
	DDRD = IN;
	
	for(;;){
		int depart = 0; 
		int cycles = 0; 

		while (cycles < MAX){
			PORTA = ROUGE;
			boucleDelai(depart);
			PORTA = ETEINT;
			boucleDelai(MAX - depart);
			
			if(depart % 3 == 0){
				cycles++;
			}
			depart++;
			
		}
		
    }
}

