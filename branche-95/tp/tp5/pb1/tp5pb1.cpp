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
 * Nom fichier: tp5pb1.cpp
 * Auteurs: Nicole Joyal, Emilio Gagnon, Jerome Desilets
 * Date: 7 fevrier 2018
 * Description: Ceci est le probleme 1 du tp5
 */

/**************************************************************************
 * Connexions
 * DEL: PORTA[1,2]
 **************************************************************************/
#define F_CPU 8000000
#include <avr/interrupt.h>
#include <avr/io.h> 
#include <util/delay.h>
const uint8_t ROUGE = (1<<0);
const uint8_t  VERT = (1<<1);
const uint8_t  ETEINT = (1<<0)&(1<<1);
volatile uint8_t ETAT = 0;
volatile bool appuye = 0;
const int IN = 0x00;
const int OUT = 0xff;
/**************************************************************************
 * Fonction 
 * Description: 
 * Return: 
 **************************************************************************/
// placer le bon type de signal d'interruption
// à prendre en charge en argument

void initialisation ( void ) {

	// cli est une routine qui bloque toutes les interruptions.
	// Il serait bien mauvais d'être interrompu alors que
	// le microcontroleur n'est pas prêt...

	cli ();

	// configurer et choisir les ports pour les entrées
	// et les sorties. DDRx... Initialisez bien vos variables
	//Initialisation des variables
	DDRA = OUT; 
	DDRD = IN;

	// cette procédure ajuste le registre EIMSK
	// de l’ATmega324PA pour permettre les interruptions externes

	EIMSK |= (1 << INT0) ;

	// il faut sensibiliser les interruptions externes aux
	// changements de niveau du bouton-poussoir
	// en ajustant le registre EICRA

	EICRA |= (1 << ISC00) ;

	// sei permet de recevoir à nouveau des interruptions.

	sei ();

}

ISR (INT0_vect) {
	uint8_t temp = 0;
	
	// laisser un delai avant de confirmer la réponse du
	// bouton-poussoir: environ 30 ms (anti-rebond)
	
	if(PIND & (1 << 2)){
		_delay_ms(30);
		// Retourne vrai des que le bouton remonte
		if (PIND & (1 << 2)){
			temp = 1;
		}
	}

	// se souvenir ici si le bouton est pressé ou relâché

	appuye=temp;

	// changements d'états tels que ceux de la
	// semaine précédente
		ETAT++;

	// Voir la note plus bas pour comprendre cette instruction et son rôle

	EIFR |= (1 << INTF0) ;

	
}
/**************************************************************************
 * Fonction boutonAppuye()
 * Description: Verifier que le bouton a ete appuye et relache completement
 * Return: vrai si bouton a ete appuye (et relache), sinon faux
 **************************************************************************/

/***************************************************
 * Fonction main()
 **************************************************/
 
int main()
{
	initialisation();
	for(;;){

        //Machine a etats
        switch(ETAT){
            case 0: //ETAT0: Etat initial
                PORTA = ROUGE;
                
                break;
            case 1: //ETAT1: Bouton appuye une premiere fois, DEL allumee ambre
                while (appuye){
                    PORTA=ROUGE;
                    _delay_us(5);
                    PORTA=VERT;
                    _delay_us(5);
                }
               
                break;
            case 2: //ETAT2: Bouton relache, DEL change en vert
                while (!appuye){
                    PORTA=VERT;
                }
                 
                break;
            case 3: //ETAT3: Tant que le bouton est appuye, la del reste rouge
                if (appuye){
                    while (appuye){
                        PORTA=ROUGE;
                    }
                }
                break;
            case 4: //ETAT4: Bouton relache, la DEL est eteinte
                while (!appuye){
                    PORTA=ETEINT;
                }
              
                break;
            case 5: //ETAT5: Bouton appuye, la DEL devient verte, puis quand relache, on
                    //revient a l'etat 0
                if (appuye){
                    while (appuye){
						PORTA = VERT;
                    }
                    ETAT=0;
                }
        }
	}
}
