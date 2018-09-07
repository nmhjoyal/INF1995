/**
 * NOM DE FICHIER : TP7_Ex1.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * DATE DE MODIFICATION : 23 fevrier 2018 
 *
 * la DEL est relie aux pins 1 et 2 du Port B 
 * le bouton est relie a la pin 3 du Port D
 **/
 
using namespace std;

#include <util/delay.h>
#include <avr/io.h> 
#include <avr/interrupt.h>

const uint8_t ROUGE = (1<<1);
const uint8_t VERT = (1<<0);
const uint8_t ETEINT = (1<<0) & (1<<1);
volatile uint8_t compteur = 0;

/************************************
 * La fonction eteindre eteint la DEL
 ************************************/
void eteindre() 
{
	PORTB = ETEINT;
}

/*************************************************
 * La fonction allumerRouge allume la DEL en rouge
 *************************************************/
void allumerRouge() 
{
	PORTB = ROUGE;
}

/*******************************************************
 * La fonction clignoterRouge fait clignoter la DEL en 
 * rouge pour compteur/2 fois, 2 fois par seconde
 *******************************************************/
void clignoterRouge(uint8_t cmp) 
{
	for(uint8_t i = 0; i < cmp/2; i++)
	{
		PORTB = ROUGE;
		_delay_ms(250);
		PORTB = ETEINT;
		_delay_ms(250);
	}
}

/************************************************
 * La fonction allumerRouge allume la DEL en vert
 ************************************************/
void allumerVert() 
{
	PORTB = VERT;
}

/**************************************************
 * Interruption si la minuterie est expiree
 **************************************************/
ISR ( TIMER1_COMPA_vect ) 
{
	compteur++; 
}

/**************************************************
 * Part la minuterie avec duree en 1/7812 sec
 **************************************************/
void partirMinuterie ( uint16_t duree ) 
{
	TCNT1 = 0; 
	OCR1A = duree;
	TCCR1A = 0;
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
	TCCR1C = 0;
	TIMSK1 |= (1 << OCIE1A);
}

 /********************************************************************************
  * La fonction boutonRelacheOuCompteurA120 part la minuterie lorsque le bouton est enfoncé et
  * retourne true lorsque le bouton est relache et false si le compteur atteint 120 avant 
  ********************************************************************************/
bool  boutonRelacheOuCompteurA120()
{ 
	if (!(PIND & 0x04)) // verifie si le bouton est appuye
	{ 
		_delay_ms(30);
		if (!(PIND & 0x04)) // verifie une 2e fois si le bouton est appuye pour l'anti-rebond
		{
			partirMinuterie((F_CPU / 1024) / 10);//part une minuterie de 1/10 seconde
			while (!(PIND & 0x04))  //tant que le bouton est appuye 
			{
				if(compteur == 120)
				{
					cli(); //arrete les interruptions (le compteur ne s'incremente plus)
					return true;
				} 	
			}
			cli(); //arrete les interruptions (le compteur ne s'incremente plus)
			return true;
		}
	}
	return false; 
}

int main()
{
	DDRD = 0x00;  // PORT D est en mode Entree    
	DDRB = 0xff;  // PORT B est en mode sortie

	enum etats { Init , Vert1 , Eteint, RougeClignotant , Vert2 }; // Enumeration des etats
	etats etat = Init;
	
	for(;;)
	{
		switch (etat)
		{
			case Init:
				compteur = 0;
				sei ();
				if (boutonRelacheOuCompteurA120())
					etat = Vert1;
				break;
		
			case Vert1:
				allumerVert(); 
				_delay_ms(500);
				etat = Eteint;
				break;
				
			case Eteint:
				eteindre(); 
				_delay_ms(2000);
				etat = RougeClignotant;
				break;
                
			case RougeClignotant:
				clignoterRouge(compteur);
				etat = Vert2;
				break;

			case Vert2:
				allumerVert();
				_delay_ms(1000);
				eteindre();
				etat = Init;
				break;
                
			default:
				break;
		}
	}
	return 0;
}
		
	
	
	
