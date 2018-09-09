/**
 * NOM DE FICHIER : testcapteur.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * DATE DE MODIFICATION : 23 fevrier 2018 
 * 
 **/
 
using namespace std;

#include <util/delay.h>
#include <avr/io.h> 
#include "Del.h"
#include "Can.h"
#include "Moteur.h"
#include "Delais.h"
#include "Capteur.h"
#include "Son.h"

/**
 * Un petit test pour s'assurer du bon fonctionnement du capteur avec
 * le convertisseur CAN. La DEL s'allume en rouge quand le capteur est 
 * a 15cms d'un mur 
 * 
 **/

void init()
{
	DDRA = 0x00;  // PORT A est en mode Entree    
	DDRB = 0xff;  // PORT B est en mode sortie
	DDRC = 0xff;  // PORT C est en mode sortie
}

/*void ajustementCapteurDroit(can &convertisseur, uint8_t & sortie, Moteur &moteur)
{
	while(!(sortie < 94 && sortie > 92)) {
		sortie = convertisseur.lecture(5) >> 2;
		if(sortie < 92) {
			moteur.ajustementMoteur(50,25,1,1);
		}
		else if(sortie > 94) {
			moteur.ajustementMoteur(25,50,1,1);
		}
	}
}

void ajustementCapteurGauche(can &convertisseur, uint8_t & sortie, Moteur &moteur)
{
	while(!(sortie < 96 && sortie > 94)) {
		sortie = convertisseur.lecture(0) >> 2;
		if(sortie < 94) {
			moteur.ajustementMoteur(25,50,1,1);
		}
		else if(sortie > 96) {
			moteur.ajustementMoteur(50,25,1,1);
		}
	}
}*/

int main()
{
	const uint8_t MAX_15CM = 76;
	const uint8_t MIN_15CM = 66;
	const uint8_t VIDE = 17;
	
	
	can convertisseur; //initialisation du convertisseur analogique-numerique
	Del led;
	Moteur moteur;
	moteur.init();
	led.eteindre();
	
	Capteur capteurGauche(&convertisseur,1,GAUCHE);
	Capteur capteurDroit(&convertisseur,2,DROIT);
	
	Son son(75);
	
	for(;;)
	{
		led.eteindre();
		while((capteurDroit.detection() > MIN_15CM) && (capteurDroit.detection() < MAX_15CM)) { //Allumer la del en rouge quand le capteur est a 15cms du mur. 95 => 1.86V
			led.allumerVert();
			moteur.avancer(); 
			son.stop();
		}
		
		while((capteurDroit.detection() <= MIN_15CM ) || capteurDroit.detection() >= MAX_15CM) {
			led.allumerRouge();
			if (capteurDroit.detection() < MIN_15CM && capteurDroit.detection() > VIDE) {
				moteur.ajustementMoteur(50,85,1,1);
				son.stop(); //ideal 85 60
			}
			else if(capteurDroit.detection() > MAX_15CM) {
				moteur.ajustementMoteur(85,50,1,1);
				son.stop();
			} else if( capteurDroit.detection() <= VIDE ) {
				son.stop();
				moteur.avancer();
				_delay_ms(500);
				moteur.arretMoteur();
						while(capteurDroit.detection() <= VIDE){
							son.start();
							moteur.ajustementMoteur(50,85,1,1);
							_delay_ms(200);
						}
			}
		}

		}
			return 0;
	}


		
	
	
	
/*
 * sans titre.cxx
 * 
 * Copyright 2018 Nicole Joyal <nijoya@l3818-14.info.polymtl.ca>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>

int main(int argc, char **argv)
{
	
	return 0;
}

