#include "../../tp8/lib/del.h"
#include "../../tp8/lib/constantes.h"
#include "../../tp8/lib/memoire_24.h"
#include "../../tp8/lib/communicationUART.h"
#include "../../tp8/lib/pwm.h"
#include "Piezoelectrique.h"
#include <stdio.h>

#include <util/delay.h>

using namespace libProjet;

enum COULEUR_DEL {eteint, rouge, vert};
    
int main()
{
	del led;
	Memoire24CXXX memoire;
	pwm moteur;
	
	DDRD = ENTREE; 
	DDRB = 0x0C; //0b0000001100
	DDRA = SORTIE; //sortie =0xFF

	Piezoelectrique piezo;

	piezo.setFrequency(50);
	
	piezo.start();
	_delay_ms(2000);
	piezo.stop();
	_delay_ms(2000);
	
	/*moteur.mettreEnMarche(50, 1);
	_delay_ms(4000);
	moteur.tournerDroite(50, 1);
	_delay_ms(4000);
	moteur.tournerGauche(50,0);
	_delay_ms(4000);
	moteur.mettreEnMarche(50, 0);
	_delay_ms(4000);
	moteur.arretterMoteur();
	*/
	moteur.ajustementPWM(0,90,1,1);
	_delay_ms(1000);
	moteur.ajustementPWM(100,100,1,1);
	_delay_ms(1000);
	moteur.ajustementPWM(100,0,1,1);
	_delay_ms(1040);
	moteur.ajustementPWM(0,0,1,1);
	for(;;)
	{
	
	}

	return 0;
}
