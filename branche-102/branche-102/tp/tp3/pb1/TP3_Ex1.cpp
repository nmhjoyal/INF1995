 /**
 * NOM DE FICHIER : TP3_Ex1.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * DATE DE MODIFICATION : Mercredi 24 Janvier 2018 
 *-------------------------------------------------
 *Etat present | Bouton poussoir (entree) | Etat suivant  | Sortie Z | 
 *   INIT      |          0               |    INIT       |    0     | 
 *   INIT      |          1               |    EA         |    0     | 
 *   EA        |          0               |    EA         |    0     | 
 *   EA        |          1               |    EB         |    0     | 
 *   EB        |          0               |    EB         |    0     | 
 *   EB        |          1               |    EC         |    0     | 
 *   EC        |          0               |    EC         |    0     | 
 *   EC        |          1               |    ED         |    0     | 
 *   ED        |          0               |    ED         |    0     | 
 *   ED        |          1               |    ROUGE      |    0     | 
 *   ROUGE     |          X               |    INIT       |    1     | 
 * 
 * EA est l'etat INIT avec compteur = 1
 * EB est l'etat INIT avec compteur = 2
 * EC est l'etat INIT avec compteur = 3
 * ED est l'etat INIT avec compteur = 4
 * 
 * Le cable relie la DEL aux pins 1 et 2 du Port B
 */

#include <util/delay.h>
#include <avr/io.h> 

const uint8_t ROUGE = (1<<1);
const uint8_t ETEINT = (1<<0) & (1<<1);
 
 /********************************************************************************
  * La fonction boutonAppuye retourne true lorsque le bouton est appuye ET relache
  ********************************************************************************/
bool  boutonAppuyeEtRelache()
{ 
	if (PIND & 0x04) 
	{ 
		_delay_ms(10);
		if (PIND & 0x04) 
		{
			while (PIND & 0x04) {} //attend que le bouton soit relache 
			return true ; 
		}
	} 
	return false ;
}

/************************************
 * La fonction eteindre eteint la DEL
 ************************************/
void eteindre() {PORTB = ETEINT;}

/*************************************************
 * La fonction allumerRouge allume la DEL en rouge
 *************************************************/
void allumerRouge() {PORTB = ROUGE;}

int main()
{
	DDRD = 0x00; // PORT D est en mode ENTREE  
	DDRB = 0xff; // PORT B est en mode SORTIE

	int compteur = 0;

	for(;;)  // boucle sans fin
	{  
		if (boutonAppuyeEtRelache() == true ) { compteur++; } 
		if (compteur == 5) 
		{
			allumerRouge();// allumer en rouge pendant 1s
			_delay_ms(1000);
			compteur = 0; // Reinitialise le compteur 
			eteindre();
		}
	} 
	return 0; 
}  


       
   




       
