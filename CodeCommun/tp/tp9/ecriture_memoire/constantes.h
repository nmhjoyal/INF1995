/**
 * NOM DE FICHIER : constantes.h
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 2 mars 2018 
 * la DEL est reliee aux pins 1 et 2 du Port B 
 *
 **/

#ifndef CONSTANTES_H
#define CONSTANTES_H


#include <avr/interrupt.h>
#include <avr/io.h> 
#include <util/delay.h>


    #define F_CPU   8000000
    #define SORTIE  0xff
    #define ENTREE  0x00

    #define ROUGE   0x01
    #define VERT    0x02
    #define ETEINT	0x00

    #define AVANCER 0
    #define RECULER 1

#endif
