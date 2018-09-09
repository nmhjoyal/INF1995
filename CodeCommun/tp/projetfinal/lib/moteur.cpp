/**
* NOM DE FICHIER : moteur.cpp
* AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
* 			 Nicole Joyal, Emilio Gagnon, J�r�me D�silets
* DATE DE MODIFICATION : 28 mars 2018
* CONNEXIONS: Moteur droit : JAUNE: D5, ORANGE: D7 
*			  Moteur gauche: JAUNE: D6, ORANGE: D8
*
**/


#include <avr/io.h>
#include "Moteur.h"

/************************************************
* Constructeur
************************************************/
Moteur::Moteur() {}

/************************************************
* Initialisation des registres reli�s au pwm des moteurs
************************************************/
void Moteur::init()
{
	DDRD |= 0xf0;
	TCCR1A |= (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);
	TCCR1B |= _BV(CS11);
	TCCR1C = 0;
	OCR1A = 0; 
	OCR1B = 0; 
}

/************************************************
* La fonction ajuste le PWM qui fait tourner les roues du robot
* Et fait tourner les moteurs dans la direction demand�e
* Direction � 1: avancer, Direction � 0: reculer
* gauche et droite = % de pwm pour le c�t� correspondant
************************************************/
void Moteur::ajustementMoteur(uint8_t gauche, uint8_t droite, uint8_t directionGauche, uint8_t directionDroite) 
{	
	OCR1A = (uint8_t)((uint16_t)(gauche)*255/100); 
	OCR1B = (uint8_t)((uint16_t)(droite)*255/100); 
	PORTD = (PORTD & 0x3F) | (directionGauche << 7) | (directionDroite << 6);
}

/************************************************
* La fonction arr�te le moteur en mettant les pwms et directions � 0
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
	//ajustementMoteur(95,91,1,1);
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

/***************************************************************
* La fonction fait tourner le robot de 90 degre vers la gauche
***************************************************************/
void Moteur::gauche90()
{
	arretMoteur();
	_delay_ms(500);
	ajustementMoteur(75,72,0,1);
	_delay_ms(725);
	arretMoteur();
	_delay_ms(500);
}

/***************************************************************
* La fonction fait tourner le robot de 90 degre vers la droit 
***************************************************************/
void Moteur::droite90()
{
	arretMoteur();
	_delay_ms(500);
	ajustementMoteur(75,72,1,0);
	_delay_ms(725);
	arretMoteur();
	_delay_ms(500);
}

/************************************************
* La fonction fait tourner le robot de 45 degre vers la droite
************************************************/	
void Moteur::droite45()
{
	arretMoteur();
	_delay_ms(500);
	ajustementMoteur(75,72,1,0);
	_delay_ms(362);
	arretMoteur();
	_delay_ms(500);
}

/************************************************
* La fonction fait tourner le robot de 45 degre vers la gauche
************************************************/	
void Moteur::gauche45()
{
	arretMoteur();
	_delay_ms(500);
	ajustementMoteur(75,72,1,0);
	_delay_ms(362);
	arretMoteur();
	_delay_ms(500);
}

/************************************************
* La fonction fait tourner le robot de 180 degr� � gauche, 
* donc un 180 degr� autour d'un point fixe et non autour de lui-m�me
************************************************/
void Moteur::autourGauche180(){
	_delay_ms(2000); //attend de d�passer le bord compl�tement
	gauche90();//tourne 2 fois � 45 degr� pour faire un 90 degr�
	avancer();
	_delay_ms(2000);//attend de d�passer le mur au complet
	gauche90();//tourne 2 fois � 45 degr� pour faire un 90 degr�
	avancer();
	_delay_ms(2000); //attend que le robot soit de nouveau vis � vis au murture(0) >> 2;
}

/************************************************
* La fonction fait tourner le robot de 180 degr� � droite, 
* donc un 180 degr� autour d'un point fixe et non autour de lui-m�me
************************************************/
void Moteur::autourDroite180(){
	_delay_ms(2000); //attend de d�passer le bord compl�tement
	droite90();//tourne 2 fois � 45 degr� pour faire un 90 degr�
	avancer();
	_delay_ms(2000);//attend de d�passer le mur au complet
	droite90();//tourne 2 fois � 45 degr� pour faire un 90 degr�
	avancer();
	_delay_ms(2000); //attend que le robot soit de nouveau vis � vis au mur
	
}

/************************************************
* La fonction ajuste le PWM qui fait tourner les roues du robot
* Et fait tourner les moteurs dans la direction demand�e
* Direction � 1: avancer, Direction � 0: reculer
* droite = % de pwm pour le c�t� correspondant
************************************************/
void Moteur::ajustementRoueDroite(uint8_t droite)
{
	uint8_t directionDroite = 1;
	if (droite > 100)
	{
		changerSigne(droite);
		directionDroite = 0;
	}
	OCR1B = (uint8_t)((uint16_t)(droite)*255/100); 
	PORTD = (PORTD & 0xbF) | (directionDroite << 6);
}

/************************************************
* La fonction ajuste le PWM qui fait tourner les roues du robot
* Et fait tourner les moteurs dans la direction demand�e
* Direction � 1: avancer, Direction � 0: reculer
* gauche = % de pwm pour le c�t� correspondant
************************************************/
void Moteur::ajustementRoueGauche(uint8_t gauche)
{
	uint8_t directionGauche = 1;
	if (gauche > 100)
	{
		changerSigne(gauche);
		directionGauche = 0;
	}
	OCR1A = (uint8_t)((uint16_t)(gauche)*255/100); 
	PORTD = (PORTD & 0x7F) | (directionGauche << 7);
}

/************************************************
* La fonction change le signe de valeur en positif
************************************************/
void Moteur::changerSigne(uint8_t& valeur)
{
	if (valeur == 0xe7) //-25
		valeur = 0x19;
	else if (valeur == 0xce) //-50
		valeur = 0x32;
	else if (valeur == 0xb5) //-75
		valeur = 0x4b;
	else if (valeur == 0x9c) //-100
		valeur = 0x64;
}



