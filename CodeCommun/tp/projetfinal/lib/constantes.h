/**
 * NOM DE FICHIER : constantes.h
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * 			 Nicole Joyal, Emilio Gagnon, Jérôme Désilets
 * DATE DE MODIFICATION : 2 mars 2018 
 * 
 **/

#ifndef CONSTANTES_H
#define CONSTANTES_H


#include <avr/interrupt.h>
#include <avr/io.h> 
#include <util/delay.h>


//Frequence CPU 

//Set ports en SORTIE ou en ENTREE
#define SORTIE  0xff
#define ENTREE  0x00


//Options de la DEL
#define ETEINT	0x00
#define ROUGE   0x01
#define VERT    0x02
#define AMBRE	0x03



//Options du moteur
#define AVANCER 0
#define RECULER 1


//Options du robot
#define DROIT 0
#define GAUCHE 1

//Varacteristiques des capteurs du robot
#define MAX_15_GAUCHE 78
#define MAX_15_DROIT 76
#define MIN_15_GAUCHE 68
#define MIN_15_DROIT 66
#define VIDE_GAUCHE 19
#define VIDE_DROIT 17

#endif
