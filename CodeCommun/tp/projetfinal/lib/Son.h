/**
 * NOM DE FICHIER : Son.h
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 2 avril 2018 
 **/
 
#ifndef SON_H
#define SON_H
 
#pragma once

#include <avr/io.h>

//Son sur PORTB, rouge=pin4, noir=pin3
class Son
{
	public:
		Son();
		Son(uint8_t note);
		void adjust(uint8_t note);
		void start();
		void stop();
		void signalPoteau();

	private:
		void init();
		
		// 8Mz/256 = 32 microsecondes
		// Temps actif (pwm) = (ms) * 8MHz / 256(prescaler)
		// ex: 142*32microsecondes = 4.545454 (temps actif de la note 45)
		uint8_t demPeriode[37] = {142, 134, 127, 119, 113,		// 45 - 49
					106, 100, 95, 89, 84, 80, 75, 71, 67, 63,	// 50 - 59
					60, 56, 53, 50, 47, 45, 42, 40, 38, 36,		// 60 - 69
					34, 32, 30, 28, 27, 25, 24, 22, 21, 20,		// 70 - 79
					19, 18};									// 80 - 81
};

#endif
