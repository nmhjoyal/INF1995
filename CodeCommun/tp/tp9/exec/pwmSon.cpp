# define F_CPU 8000000UL

#include "pwmSon.h"

pwmSon::pwmSon()
{
	init();
}

pwmSon::pwmSon(uint8_t max)
{
	init();
	adjust(max);
}

void pwmSon::init()
{
	DDRA = 0xFF;
	
    // Counter to 0
    TCNT0 = 0;

    TCCR0A |= _BV(WGM01); // CTC

	// division d'horloge par 256
    TCCR0B |= _BV(CS02);
}

void pwmSon::adjust(uint8_t max)
{
	OCR0A = max;
}

void pwmSon::start()
{
	TCCR0A |= _BV(COM0A0); // Toggle OC0A on Compare Match (Set output to high level).
}

void pwmSon::stop()
{
	TCCR0A &= ~(_BV(COM0A1)) & ~(_BV(COM0A0)); 
}
