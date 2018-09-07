//TABLEAU D'ETATS
/**********************************************************************************
*   EP  *  A  *  ES    *   Z    *                 Commentaires                    *
***********************************************************************************
* ETAT0 *  0  * ETAT0  * ETEINT * Compteur <5                                     *
* ETAT0 *  1  * ETAT1  * ETEINT * Compteur =5									  *
* ETAT1 *  0  * ETAT0  * ROUGE  * Compteur =0; Lumiere eteinte apres 1 seconde    * 
**********************************************************************************/
//LEGENDE: EP=Etat Present; ES= Etat suivant;
// A = entree (bouton): 1 quand compteur = 5; Z= sortie (del)



/*
 * Nom fichier: tp3pb1.cpp
 * Auteurs: Nicole Joyal, Emilio Gagnon, Jerome Desilets
 * Date: 24 janvier 2018
 * Description: Ceci est le probleme 1 du tp3
 */

/**************************************************************************
 * Connexions
 * DEL: PORTA[1,2]
 **************************************************************************/


#define F_CPU 8000000

#include <avr/io.h> 
#include <util/delay.h>

const uint8_t ROUGE = (1<<0);
const uint8_t  VERT = (1<<1);
const uint8_t  ETEINT = (1<<0)&(1<<1);

const int IN = 0x00;
const int OUT = 0xff;

/**************************************************************************
 * Fonction boutonAppuye()
 * Description: Verifier que le bouton a ete appuye et relache completement
 * Return: vrai si bouton a ete appuye (et relache), sinon faux
 **************************************************************************/
 
bool boutonAppuye(){
	//False par defaut
	bool appuye = false;
	
	if(PIND & (1 << 2)){
		_delay_ms(10);
		
		// Retourne vrai des que le bouton remonte
		while (PIND & (1 << 2)){
			appuye = true;
		}
	}
	return appuye;
}

/***************************************************
 * Fonction main()
 **************************************************/
 
int main()
{
	//Initialisation des variables
	uint8_t compteur = 0x00;
  
	for(;;){
		
		if (boutonAppuye()){
			//Compteur incremente lorsque boutonAppuye retourne vrai
			compteur++;
		}
		
		//Si bouton pese 5 fois, on allume la DEL (pendant 1sec.)
		if (compteur == 0b00000101){
			PORTA = ROUGE;
			_delay_ms(1000);
			
			//Reinitialisation
			PORTA = ETEINT;
			compteur = 0;
		} 
	}
}
