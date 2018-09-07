/**
 * NOM DE FICHIER : delais.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 12 mars 2018 
 * sers à faire une fonction delays_ qui peut prendre une variable en paramètre
 *
 **/


#include "delais.h"

using namespace libProjet;

void delais::delaisVariableUs(uint8_t n){
	for (uint8_t i = 0; i < n; i++) // applique n fois un delais de 10 us
	{
		_delay_us(10); 
	}
}

void delais::delaisVariableMs(uint8_t n){
	for (uint8_t i = 0; i < n; i++) // applique n fois un delais de 1 ms
	{
		_delay_ms(1); 
	}
}
