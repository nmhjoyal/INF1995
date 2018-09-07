/**
* NOM DE FICHIER : moteur.cpp
* AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
* 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
* DATE DE MODIFICATION : 28 mars 2018
* CONNEXIONS: Moteur droit : JAUNE: D5, ORANGE: D7 
*			  Moteur gauche: JAUNE: D6, ORANGE: D8
*
**/

#pragma once

#include <avr/io.h>

#include "moteur.h"

/************************************************
* Initialisation des registres reliés au pwm des moteurs
************************************************/
Moteur::Moteur()
{
	DDRD = SORTIE;
	TCCR1A |= (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);
	TCCR1B |= _BV(CS11);
	TCCR1C = 0;
	OCR1A = 0; 
	OCR1B = 0; 
}

/************************************************
* La fonction ajuste le PWM qui fait tourner les roues du robot
* Et fait tourner les moteurs dans la direction demandée
* Direction à 1: avancer, Direction à 0: reculer
* gauche et droite = % de pwm pour le côté correspondant
************************************************/
void Moteur::ajustementMoteur(uint8_t gauche, uint8_t droite, uint8_t directionGauche, uint8_t directionDroite) 
{	

	OCR1A = (uint8_t)((uint16_t)(gauche)*255/100); 
	OCR1B = (uint8_t)((uint16_t)(droite)*255/100); 
	PORTD = (PORTD & 0x3F) | (directionGauche << 7) | (directionDroite << 6);
}

/************************************************
* La fonction arrête le moteur en mettant les pwms et directions à 0
************************************************/
void Moteur::arretMoteur() 
{
	ajustementMoteur(0,0,0,0);
}

/************************************************
* La fonction fait avancer le robot avec un PWM de 75%
************************************************/
void Moteur::avancer()
{
	ajustementMoteur(75,72,1,1);
}

/************************************************
* La fonction fait reculer le robot avec un PWM de 75%
************************************************/	
void Moteur::reculer()
{
	ajustementMoteur(75,72,0,0);
}

/************************************************
* La fonction fait tourner le robot de 180 degre vers la droite
************************************************/	
void Moteur::droite180()
{
	arretMoteur();
	_delay_ms(500);
	ajustementMoteur(75,72,1,0);
	_delay_ms(1450);
	arretMoteur();
	_delay_ms(500);
}

/************************************************
* La fonction fait tourner le robot de 180 degre vers la gauche
************************************************/
void Moteur::gauche180()
{
	arretMoteur();
	_delay_ms(500);
	ajustementMoteur(75,72,0,1);
	_delay_ms(1450);
	arretMoteur();
	_delay_ms(500);
}
