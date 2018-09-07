 /**
 * NOM DE FICHIER : TP5_Ex1.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * DATE DE MODIFICATION : 7 fevrier 2018 
 **/
 

#include <util/delay.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include "memoire_24.h"

const uint8_t ROUGE = (1<<1);
const uint8_t VERT = (1<<0);
const uint8_t ETEINT = (1<<0) & (1<<1);
const uint16_t addresse = 0x00;
bool compare = true; 

using namespace std; 

int main()
{
	DDRB = 0xFF; //Mettre le port B en sortie
	PORTB = ETEINT; 
	Memoire24CXXX memoire;  
	uint8_t texte[] = {"*E*C*O*L*E* *P*O*L*Y*T*E*C*H*N*I*Q*U*E*\0"}; 
	const uint8_t longueur = sizeof(texte);
	
	memoire.ecriture(addresse, texte, longueur);
	
	_delay_ms(5);
	
	uint8_t texteLu[longueur]; 
	
	memoire.lecture(addresse, texteLu, longueur); 
	
	for (uint8_t i = 0; i < longueur; i++) 
	{
		if(texte[i] != texteLu[i])
		{
			compare = false;
		}
	}
	
	if (compare)
	{
		PORTB = VERT; 
			
	} else {
		
		PORTB = ROUGE;
	}
	
	return 0;     
}  
   
