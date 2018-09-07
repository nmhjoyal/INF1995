/**
* NOM DE FICHIER : pwm.cpp
* AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
* 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
* DATE DE MODIFICATION : 12 mars 2018
* moteur relié au port D
*
**/

#pragma once

#include <avr/io.h>

#include "pwm.h"

using namespace libProjet;

/************************************************
* La fonction ajuste le PWM qui fait tourner les roues du robot
* Et fait tourner les moteurs dans la direction demandée
************************************************/
void pwm::ajustementPWM (uint8_t droite, uint8_t gauche, uint8_t directionGauche, uint8_t directionDroite) 
{	
	DDRD = 0xff;  // PORT D est en mode sortie
	TCCR1A |= (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);
	TCCR1B |= _BV(CS11);
	TCCR1C = 0;

	OCR1A = (uint8_t)((uint16_t)(droite)*255/100); 
	OCR1B = (uint8_t)((uint16_t)(gauche)*255/100); 
	
	//roue gauche: pins 5 et 7 (fil jaune) PORTD, jaune vers bas sur port JM2
	//roue droite: pins 6 et 8 (fil jaune) PORTD, jaune vers bas sur port JM1 
	PORTD = (PORTD & 0b00111111) | (directionGauche << 6) | (directionDroite << 7);
}

/************************************************
* La fonction arrête le moteur en mettant les registres
* à 0.
************************************************/
void pwm::arretMoteur() 
{
	//registres mis à 0;
	OCR1A = 0; 
	OCR1B = 0; 
}
