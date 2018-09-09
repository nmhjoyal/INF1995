#include <stdio.h>
#include <util/delay.h>
#include "moteur.h"


//déterminer proportion pwm moteur gauche vs moteur droit
//DROIT = 96% de GAUCHE

//TODO
//Changer librairie à celle du projet final


int main()
{ 
	
	DDRB = SORTIE;
	Moteur robot;
	
	robot.init();

	
	
	//robot.avancer();
	_delay_ms(3600);
	robot.avancer();
	robot.autourGauche180();
	
	_delay_ms(3000);
		
	robot.arretMoteur();	
	
	return 0;
}
