#include "Moteur.h"

Moteur::Moteur() {}

Moteur::~Moteur() {}

void Moteur::mettreEnMarche(uint8_t frequence, uint8_t direction)
{
	pwm_.ajustementPWM(frequence, frequence, direction, direction);
}

void Moteur::tournerDroite(uint8_t frequence, uint8_t direction) 
{
	pwm_.ajustementPWM(0, frequence, direction, direction);
}


void Moteur::tournerGauche(uint8_t frequence, uint8_t direction) 
{
	pwm_.ajustementPWM(frequence, 0, direction, direction);
}


void Moteur::arretterMoteur()
{
	pwm_.arretMoteur();
}
