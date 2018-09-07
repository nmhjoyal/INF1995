/*
 * Nom fichier: tp4pb2.cpp
 * Auteurs: Nicole Joyal, Emilio Gagnon, Jerome Desilets
 * Date: 31 janvier 2018
 * Description: Ceci est le probleme 2 du tp4
 */

/**************************************************************************
 * Connexions
 * DEL: PORTA[1,2]
 **************************************************************************/

#define F_CPU 8000000
 
#include <avr/io.h> 
#include <util/delay.h>

const uint8_t OFF = 0;
const uint8_t ON = 1;

const int IN = 0x00;
const int OUT = 0xff;
static const int MAX = 400; 

/**************************************************************************
 * Fonction boucleDelai()
 * Description: Faire un delai selon la frequence
 * Parametre in: Max - nbDepart de microsecondes de delai
 **************************************************************************/
 
 void boucleDelai(int nbDepart){
	if (nbDepart >= 0){
		for(int a=0; a<nbDepart; a++){
			_delay_ms(1);
		}
	}
 }

/***************************************************
 * Fonction main()
 **************************************************/
 
int main()
{
	//Initialisation des variables
	DDRB = OUT;
	PORTB = 0;
	
	int nbCycles = 2*60;	
	int periode = round(1000/60);
	
	
  
	for(;;){
		
		for(int i=0;i<nbCycles;i++){
			PORTB = OFF;
			boucleDelai(periode);
		}
		
		for(int i=0;i<nbCycles;i++){
			PORTB = 0b11;
			boucleDelai(round(periode/4));
			PORTB = OFF;
			boucleDelai(round(3*periode/4)); 
			
		}
		for(int i=0;i<nbCycles;i++){
			PORTB = 0b11;
			boucleDelai(round(periode/2));
			PORTB = OFF;
			boucleDelai(round(periode/2)); 
			
		}
		for(int i=0;i<nbCycles;i++){
			PORTB = 0b11;
			boucleDelai(round(3*periode/4));
			PORTB = OFF;
			boucleDelai(round(periode/4)); 
			
		}
		
		for(int i=0;i<nbCycles;i++){
			PORTB = 0b11;
			boucleDelai(periode);
			PORTB = OFF;			
		}
		
		/////400Hz
		nbCycles = 800;
		periode = round(1000/400);
		
		for(int i=0;i<nbCycles;i++){
			PORTB = OFF;
			boucleDelai(periode);
		}
		
		for(int i=0;i<nbCycles;i++){
			PORTB = 0b11;
			boucleDelai(round(periode/4));
			PORTB = OFF;
			boucleDelai(round(3*periode/4)); 
			
		}
		for(int i=0;i<nbCycles;i++){
			PORTB = 0b11;
			boucleDelai(round(periode/2));
			PORTB = OFF;
			boucleDelai(round(periode/2)); 
			
		}
		for(int i=0;i<nbCycles;i++){
			PORTB = 0b11;
			boucleDelai(round(3*periode/4));
			PORTB = OFF;
			boucleDelai(round(periode/4)); 
			
		}
		
		for(int i=0;i<nbCycles;i++){
			PORTB = 0b11;
			boucleDelai(periode);
			PORTB = OFF;			
		}
		
		
		
	}
    
}
