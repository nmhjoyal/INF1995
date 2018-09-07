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


	for(;;)
	{	/*
		 
		 robot.avancer();
		 _delay_ms(1500);
		 robot.arretMoteur();
		 _delay_ms(500);
		 
		  robot.reculer();
		 _delay_ms(1500);
		 robot.arretMoteur();
		 _delay_ms(500);
		 
		 robot.droite180();
		 robot.gauche180();
		 
		
		//AVANCER	
		pwm.ajustementMoteur(75,72,1,1);
		_delay_ms(1500);
		//RECULER
		//pwm.ajustementPWM(75,72,0,0);
		
		//180 DROITE (1 ROUE)
		pwm.ajustementPWM(0,0,0,0);
		_delay_ms(500);
		pwm.ajustementPWM(75,0,0,1);
		_delay_ms(2250);
		pwm.ajustementPWM(0,0,0,0);
		_delay_ms(500);

		//180 DROITE (2ROUES)
		pwm.arretMoteur();
		_delay_ms(500);
		pwm.ajustementMoteur(75,72,1,0);
		_delay_ms(1450);
		pwm.arretMoteur();
		_delay_ms(500);

		//180 GAUCHE (2ROUES)
		pwm.arretMoteur();
		_delay_ms(500);
		pwm.ajustementMoteur(75,72,0,1);
		_delay_ms(1450);
		pwm.arretMoteur();
		_delay_ms(500);
		*/
		
	}
		
	
	return 0;
}
