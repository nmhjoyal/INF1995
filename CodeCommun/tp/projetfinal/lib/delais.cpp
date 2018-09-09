/**
 * NOM DE FICHIER : delais.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 28 mars 2018 
 **/

#include "Delais.h"


/******************************************
 * sert à faire une fonction delays_ qui 
 * peut prendre une variable en paramètre
 ******************************************/
 
 // applique n fois un delais de 10 us
void Delais::delaisVariableUs(uint8_t n){
	for (uint8_t i = 0; i < n; i++) 
	{
		_delay_us(10); 
	}
}

// applique n fois un delais de 1 ms
void Delais::delaisVariableMs(uint8_t n){
	for (uint8_t i = 0; i < n; i++) 
	{
		_delay_ms(1); 
	}
}
