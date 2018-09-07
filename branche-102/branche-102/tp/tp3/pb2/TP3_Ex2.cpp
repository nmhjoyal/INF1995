/**
 * NOM DE FICHIER : TP3_Ex2.cpp
 * AUTEURS : Pascale Sylvestre, Yuri Azar, William Valiquette
 * DATE DE MODIFICATION : Mercredi 24 Janvier 2018
 * -------------------------------------------------
 *Etat present | Bouton poussoir (entree) | Etat suivant  | Sortie Z     | 
 *   INIT      |          0               |    INIT       |   Rouge      | 
 *   INIT      |          1               |    AMBRE      |   Rouge      | 
 *   AMBRE     |          1               |    AMBRE      |   Ambre      | 
 *   AMBRE     |          0               |    VERT1      |   Ambre      | 
 *   VERT1     |          0               |    VERT1      |   Vert       | 
 *   VERT1     |          1               |    ROUGE      |   Vert       | 
 *   ROUGE     |          1               |    ROUGE      |   Rouge      | 
 *   ROUGE     |          0               |    ETEINT     |   Rouge      |        
 *   ETEINT    |          0               |    ETEINT     |   Eteint     | 
 *   ETEINT    |          1               |    VERT2      |   Eteint     | 
 *   VERT2     |          1               |    VERT2      |   Vert       |  
 *   VERT2     |          0               |    INIT       |   Vert       | 
 * 
 * Le cable relie la DEL aux pins 1 et 2 du Port B
 */
 
#include <util/delay.h>
#include <avr/io.h> 

const uint8_t ROUGE = (1<<1);
const uint8_t VERT = (1<<0);
const uint8_t ETEINT = (1<<0) & (1<<1);

/*
 * La fonction boutonAppuye retourne true lorsque le bouton est appuye
 */
bool  boutonAppuye()
{ 
	if (PIND & 0x04) 
	{ 
		_delay_ms(10);
		if (PIND & 0x04) {return true;}
	} 
	return false ;
}

/************************************
 * La fonction eteindre eteint la DEL
 ************************************/
void eteindre() {PORTB = ETEINT;}

/*************************************************
 * La fonction allumerRouge allume la DEL en rouge
 *************************************************/
void allumerRouge() {PORTB = ROUGE;}

/************************************************
 * La fonction allumerRouge allume la DEL en vert
 ************************************************/
void allumerVert() {PORTB = VERT;}

/********************************************************************************
 * La fonction allumerAmbre appelle en alternance allumerRouge() et allumerVert() 
 * avec un delais de 5 ms tant que le bouton reste appuye
 ********************************************************************************/
void allumerAmbre()
{
	while(boutonAppuye())
	{     
		allumerRouge ();
		_delay_ms(5);  
		allumerVert ();
		_delay_ms(5);  
	}    
}


int main()
{
	DDRD = 0x00;  // PORT D est en mode Entree    
	DDRB = 0xff;  // PORT B est en mode sortie
	enum etats { Init , Ambre , Vert1 , Rouge , Eteint , Vert2 }; // Enumeration des etats

	etats etat = Init;
	for(;;)  // boucle sans fin
	{  
		switch (etat)
		{
			case Init:
				allumerRouge();
				if (boutonAppuye()) {etat = Ambre;}
				break;
				
			case Ambre:
				allumerAmbre();
				if (!boutonAppuye()) {etat = Vert1;}
				break;
                
			case Vert1:
				allumerVert(); 
				if (boutonAppuye()) {etat = Rouge;}
				break;
                
			case Rouge:
				allumerRouge();
				if (!boutonAppuye()) {etat = Eteint;}
				break;

			case Eteint:
				eteindre();
				if (boutonAppuye()) {etat = Vert2;}
				break;
                
			case Vert2:
				allumerVert();
				if (!boutonAppuye()) {etat = Init;}
				break;
			
			default:
				break;
		}
	}
	return 0;     
}  
   
