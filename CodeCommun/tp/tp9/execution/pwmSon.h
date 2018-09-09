#pragma once

#include <avr/io.h>



class pwmSon
{
	public:
		pwmSon();
		pwmSon(uint8_t ratio255);
		void adjust(uint8_t ratio255);
		void start();
		void stop();

	private:
		void init();
};


