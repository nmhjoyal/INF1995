#pragma once

#include "../../tp8/lib/pwm.h"

using namespace std;
using namespace libProjet;

class Moteur 
{
	public:
		Moteur();
		~Moteur();
		
		void mettreEnMarche(uint8_t frequence, uint8_t direction);
		void tournerDroite(uint8_t frequence, uint8_t direction);
		void tournerGauche(uint8_t frequence, uint8_t direction);
		void arretterMoteur();
	
	private:
		pwm pwm_;
		
};

