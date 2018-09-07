/**
 * NOM DE FICHIER : main.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 12 mars 2018 
 * test de la librairie
 *
 **/

#include "../lib/del.cpp"

 using namespace libProjet;

/**
 * fonction main qui main function. 
 */
int main()
{
	DDRB = 0xff;
	
	del led;
	
	for(;;)
	{
		led.allumerRouge();
		_delay_ms(1000);
		led.allumerVert();
		_delay_ms(1000);
	}
    return 0; 
}
