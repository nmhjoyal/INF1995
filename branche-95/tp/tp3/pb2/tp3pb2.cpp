//TABLEAU D'ETATS
/********************************
*   EP  *  A  *  ES    *   Z    *
*********************************
* ETAT0 *  0  * ETAT0  * ROUGE  *
* ETAT0 *  1  * ETAT1  * ROUGE  * 
* ETAT1 *  0  * ETAT2  * ORANGE *
* ETAT1 *  1  * ETAT1  * ORANGE *
* ETAT2 *  0  * ETAT2  * VERT   *   
* ETAT2 *  1  * ETAT3  * VERT   *
* ETAT3 *  0  * ETAT4  * ROUGE  *
* ETAT3 *  1  * ETAT3  * ROUGE  *
* ETAT4 *  0  * ETAT4  * ETEINT *
* ETAT4 *  1  * ETAT5  * ETEINT *
* ETAT5 *  1  * ETAT5  * VERT   *
* ETAT5 *  0  * ETAT0  * VERT   *
*********************************/
//LEGENDE: EP=Etat Present; ES= Etat suivant;
// A = entree (bouton); Z= sortie (del)


/*
 * Nom fichier: tp3pb2.cpp
 * Auteurs: Nicole Joyal, Emilio Gagnon, Jerome Desilets
 * Date: 26 janvier 2018
 * Description: Ceci est le probleme 2 du tp3
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
	if(PIND & (1 << 2)){
		_delay_ms(10);
		
		// Retourne vrai des que le bouton remonte
		while (PIND & (1 << 2)){
			return true;
		}
	}
	return false;
}


/***************************************************
 * Fonction main()
 **************************************************/
 
int main()
{
	//Initialisation des variables
	DDRA = OUT; 
	DDRD = IN;
	uint8_t ETAT = 0x00;
  
	for(;;){

        //Machine a etats
        switch(ETAT){
            case 0: //ETAT0: Etat initial
                PORTA = ROUGE;
                if (boutonAppuye()){
                    ETAT++; 
                }
                break;
            case 1: //ETAT1: Bouton appuye une premiere fois, DEL allumee ambre
                while (boutonAppuye()){
                    PORTA=ROUGE;
                    _delay_ms(5);
                    PORTA=VERT;
                }
                ETAT++;
                break;
            case 2: //ETAT2: Bouton relache, DEL change en vert
                while (!boutonAppuye()){
                    PORTA=VERT;
                }
                ETAT++; 
                break;
            case 3: //ETAT3: Tant que le bouton est appuye, la del reste rouge
                if (boutonAppuye()){
                    while (boutonAppuye()){
                        PORTA=ROUGE;
                    }
                    ETAT++;
                }
                break;
            case 4: //ETAT4: Bouton relache, la DEL est eteinte
                while (!boutonAppuye()){
                    PORTA=ETEINT;
                }
                ETAT++;
                break;
            case 5: //ETAT5: Bouton appuye, la DEL devient verte, puis quand relache, on
                    //revient a l'etat 0
                if (boutonAppuye()){
                    while (boutonAppuye()){
                        PORTA=VERT;
                    }
                    ETAT=0;
                }
        }

    }	
}
