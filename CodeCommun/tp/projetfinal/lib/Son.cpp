/**
 * NOM DE FICHIER : Son.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 2 avril 2018 
 **/

#include "Son.h"
#include "Constantes.h"

Son::Son()
{
	init();
}

Son::Son(uint8_t note)
{
	init();
	adjust(note);
}

/************************************
 * La fonction set les pin pour pouvoir généré le PWM
 ************************************/
void Son::init()
{
	DDRB |= 0x0c;

    // Counter to 0
    TCNT0 = 0;

    TCCR0A |= 1<<(WGM01); // CTC

	// division d'horloge par 256
    TCCR0B |= 1<<(CS02);
}

/************************************
 * La fonction ajuste le temps actif 
 * en prenant la valeur correspondant 
 * à la note dans le tableau demperiode
 ************************************/
void Son::adjust(uint8_t note)
{
	if(note >= 45 && note <= 81){
		OCR0A = demPeriode[note - 45];
	}	
}

/************************************
 * La fonction pars le compteur
 ************************************/
void Son::start()
{
	TCCR0A |= 1<<(COM0A0); // Toggle OC0A on Compare Match (Set output to high level).
}

/************************************
 * La fonction arrête le compteur
 ************************************/
void Son::stop()
{
	TCCR0A &= ~(_BV(COM0A1)) & ~(_BV(COM0A0)); 
}

/************************************
 * 3 signaux de 200 ms et pause de 100 ms
 ************************************/
void Son::signalPoteau(){
	adjust(55);
	start();
	_delay_ms(200);
	stop();
	_delay_ms(100);
	start();
	_delay_ms(200);
	stop();
	_delay_ms(100);
	start();
	_delay_ms(200);
	stop();
}
