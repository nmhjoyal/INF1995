/**
 * NOM DE FICHIER : diagnostic.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 4 avril 2018 
 * Ecriture de
 *
 **/

#include "Bouton.h"
#include "Can.h"
#include "Capteur.h"
#include "CommunicationUART.h"
#include "Constantes.h"
#include "Del.h"
#include "Moteur.h"
#include <stdio.h>
#include <avr/interrupt.h>

volatile uint8_t lecture[2];
volatile uint8_t compteur = 0;

void action()
{
	Del del;
	Moteur moteur; 
	
	switch (lecture[0])
	{
		case 0xf8 : 
			moteur.ajustementRoueGauche(lecture[1]);
			break;

		case 0xf9 : 
			moteur.ajustementRoueDroite(lecture[1]);
			break;

		case 0xfa : 
			if (lecture[1] == 0)
				del.eteindre();
			else if (lecture[1] == 1)
				del.allumerVert();
			else if (lecture[1] == 2)
				del.allumerRouge();
			break;
	}
}


ISR(USART0_RX_vect)
{	
	uint8_t valeur = UDR0;
	uint8_t pos = compteur%2;
	lecture[pos] = valeur;
	if (pos == 1)
		action();
	compteur++;
}

void identification(CommunicationUART& uart)
{
	
	uart.transmissionUART(0xf0);
	uart.transmissionUART('F');
	uart.transmissionUART('r');
	uart.transmissionUART('o');
	uart.transmissionUART('b');
	uart.transmissionUART('i');
	uart.transmissionUART('e');
	uart.transmissionUART(' ');
	uart.transmissionUART('R');
	uart.transmissionUART('o');
	uart.transmissionUART('t');
	uart.transmissionUART('r');
	uart.transmissionUART('i');
	uart.transmissionUART('e');
	
	//numero equipe
	uart.transmissionUART(0xf1); 
	uart.transmissionUART('9');
	uart.transmissionUART('5');
	uart.transmissionUART('-');
	uart.transmissionUART('1');
	uart.transmissionUART('0');
	uart.transmissionUART('2');

	//numero de la section
	uart.transmissionUART(0xf2);
	uart.transmissionUART(0x05);

	//session
	uart.transmissionUART(0xf3);
	uart.transmissionUART('1');
	uart.transmissionUART('8');
	uart.transmissionUART('-');
	uart.transmissionUART('1');

	//couleur
	uart.transmissionUART(0xf4);
	uart.transmissionUART(0x01);
}



uint8_t conversionGauche(uint8_t val){
	if (val > 82  ){
		return 0;
	}
	else if (val > 64){
		return 12;
	}
	else if (val > 51){
		return 17;
	}
	else if (val > 44){
		return 22;
	}
	else if (val > 38){
		return 27;
	}
	else if (val > 34){
		return 32;
	}
	else if (val > 30){
		return 37;
	}
	else if (val > 28){
		return 42;
	}
	else if (val > 24){
		return 47;
	}
	else if (val > 20){
		return 52;
	}
	else if (val > 18){
		return 57;
	}
	else if (val > 16){
		return 62;
	}
	else if (val > 14){
		return 67;
	}
	else if (val > 12){
		return 72;
	}
	else if (val > 8){
		return 77;
	}
	else {
		return 82;
	}
}

uint8_t conversionDroit(uint8_t val){
	if (val > 80  ){
		return 0;
	}
	else if (val > 62){
		return 12;
	}
	else if (val > 49){
		return 17;
	}
	else if (val > 42){
		return 22;
	}
	else if (val > 36){
		return 27;
	}
	else if (val > 31){
		return 32;
	}
	else if (val > 28){
		return 37;
	}
	else if (val > 23){
		return 42;
	}
	else if (val > 20){
		return 47;
	}
	else if (val > 18){
		return 52;
	}
	else if (val > 16){
		return 57;
	}
	else if (val > 13){
		return 62;
	}
	else if (val > 11){
		return 67;
	}
	else if (val > 9){
		return 72;
	}
	else if (val > 6){
		return 77;
	}
	else {
		return 82;
	}
}

uint8_t conversionDroite2(uint8_t val){
	if (val > 100 ){
		return 0;
	}
	else if (val > 74){
		return 12;
	}
	else if (val > 59){
		return 17;
	}
	else if (val > 49){
		return 22;
	}
	else if (val > 42){
		return 27;
	}
	else if (val > 36){
		return 32;
	}
	else if (val > 32){
		return 37;
	}
	else if (val > 28){
		return 42;
	}
	else if (val > 26){
		return 47;
	}
	else if (val > 23){
		return 52;
	}
	else if (val > 20){
		return 57;
	}
	else if (val > 18){
		return 62;
	}
	else if (val > 16){
		return 67;
	}
	else if (val > 15){
		return 72;
	}
	else if (val > 13){
		return 77;
	}
	else {
		return 82;
	}
}


uint8_t conversionGauche2(uint8_t val){
	if (val > 102 ){
		return 0;
	}
	else if (val > 74){
		return 12;
	}
	else if (val > 60){
		return 17;
	}
	else if (val > 50){
		return 22;
	}
	else if (val > 43){
		return 27;
	}
	else if (val > 37){
		return 32;
	}
	else if (val > 33){
		return 37;
	}
	else if (val > 29){
		return 42;
	}
	else if (val > 27){
		return 47;
	}
	else if (val > 24){
		return 52;
	}
	else if (val > 22){
		return 57;
	}
	else if (val > 19){
		return 62;
	}
	else if (val > 18){
		return 67;
	}
	else if (val > 17){
		return 72;
	}
	else if (val > 15){
		return 77;
	}
	else {
		return 82;
	}
}
uint8_t moyenne(uint8_t val[])
{
	uint32_t moyenne = 0;
	for (uint8_t i = 0; i<200; i++){
		moyenne += val[i];
	}
	moyenne /= 200;
	return uint8_t(moyenne);
}

int main()
{	

	cli();

	Del del;
	Bouton bouton;
	CommunicationUART uart;
	uart.initialisationUART();
	Moteur moteur; 
	moteur.init();
	can convertisseur;
	Capteur capteurDroit(&convertisseur, 2, 10, DROIT);
	Capteur capteurGauche(&convertisseur, 1, 10, GAUCHE);
	
	uint8_t donneeRecue = 0x00;


	//on attend que 0xfb soit recu avant d'envoyer les informations
	while (donneeRecue != 0xfb){
		donneeRecue = uart.receiveUART();
	} 
	identification(uart);

	_delay_ms(500);
	uart.receiveUART(); //important si non il y a un 0000 de trop en lecture
	
	sei();
	
	for(;;)
	{	
		
		//bouton interrupt
		uart.transmissionUART(0xf5);
		uart.transmissionUART(bouton.statut());

		//capteur gauche
		uart.transmissionUART(0xf6);
		uint8_t distanceGauche[200];
		for (uint8_t i = 0; i<200; i++){
			distanceGauche[i] = capteurGauche.detection();
		}
		uart.transmissionUART(conversionGauche2(moyenne(distanceGauche)));
		
		//capteur droitDroit
		uart.transmissionUART(0xf7);
		uint8_t distanceDroit[200];
		for (uint8_t i = 0; i<200; i++){
			distanceDroit[i] = capteurDroit.detection();
		}
		uart.transmissionUART(conversionDroite2(moyenne(distanceDroit)));
	}
}
