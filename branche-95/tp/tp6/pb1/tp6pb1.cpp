/*
 * Nom fichier: tp6pb1.cpp
 * Auteurs: Nicole Joyal, Emilio Gagnon, Jerome Desilets
 * Date: 14 fevrier 2018
 * Description: Ceci est le probleme 1 du tp6
 */

/**************************************************************************
 * Connexions
 * DEL: PORTA[1,2]
 **************************************************************************/


#define F_CPU 8000000

#include <avr/io.h> 
#include <util/delay.h>
#include "memoire_24.h"
#include <string.h>


const uint8_t ROUGE = (1<<0);
const uint8_t  VERT = (1<<1);
const uint8_t  ETEINT = (1<<0)&(1<<1);

const int IN = 0x00;
const int OUT = 0xff;

/**************************************************************************
 * Fonction init()
 * Description: Initialiser
 **************************************************************************/
 
void init(){
	DDRA = OUT; 
	DDRD = IN;
}

/**************************************************************************
 * Fonction comparer()
 * Description: Comparer duhhhhhh
 * Retour: vrai ou faux...
 **************************************************************************/
 
 bool comparer(uint8_t* chaineCaract, uint8_t* donneeLue) {
	
	
	for (uint8_t i = 0; i < 41; i++){
		if(chaineCaract[i] == donneeLue[i]){
			
		}	
		else {
			return false;
		}
	}
	return true;
	
 }


/***************************************************
 * Fonction main()
 **************************************************/
 
int main()
{
	init();
	Memoire24CXXX memoire;
	uint8_t chaineCaract[41] = {"*E*C*O*L*E* *P*O*L*Y*T*E*C*H*N*I*Q*U*E*\0"};
	memoire.ecriture(0x00, chaineCaract, sizeof(chaineCaract));
	_delay_ms(5);
	uint8_t donneeLue[41];
	memoire.lecture(0x00, donneeLue, sizeof(chaineCaract));
		
		
	if (comparer(chaineCaract, donneeLue))
	{
		PORTA = VERT; 
	}else{
		PORTA = ROUGE;
	}
	
	for(;;);
}
