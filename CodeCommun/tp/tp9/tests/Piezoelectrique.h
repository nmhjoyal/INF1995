#pragma once

#include "pwmSon.h"
 
class Piezoelectrique
{

	public:
		Piezoelectrique();
		Piezoelectrique(uint8_t frequency);
		~Piezoelectrique();

		void start();
		void stop();

		void setFrequency(uint8_t note);

	private:
		pwmSon generateur_;
		uint8_t demPeriode[37];
		
};

