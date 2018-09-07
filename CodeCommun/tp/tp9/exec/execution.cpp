#include "../../tp8/lib/del.cpp"
#include "../../tp8/lib/constantes.h"
#include "../../tp8/lib/memoire_24.h"
#include "../../tp8/lib/communicationUART.h"
#include "../../tp8/lib/pwm.h"
#include "../../tp8/lib/delais.h"
#include "Piezoelectrique.h"
#include <stdio.h>

#include <util/delay.h>

// applique n fois un delais de 25 ms
void delaisVariableMs(uint8_t n){
	for (uint8_t i = 0; i < n; i++) 
	{
		_delay_ms(25); 
	}
}


using namespace libProjet;
int main()
{ 
	del led;
	communicationUART uart;
	Memoire24CXXX memoire;
	
	uint16_t base_pointer = 0;
	uint8_t boucle_iter = 0;

	bool dbtTrouve = false;
	bool finTrouve = false;
	
	DDRB = SORTIE;
	DDRD = SORTIE;
	

	uint16_t i = 2;
	
	pwm pwm; 
	Piezoelectrique piezo;
	
	uint8_t nombreInstructions;
	memoire.lecture(1, &nombreInstructions);
	nombreInstructions -= 2;
	
	pwm.arretMoteur();
	while (i < nombreInstructions && !finTrouve)
	{
		uint8_t data[2];
		memoire.lecture(i, data, 2);
		
		
		if (dbtTrouve)
		{
			switch(data[0]) 
			{
				case 0x02:
					delaisVariableMs(data[1]);
					break;
				
				case 0x44:
					//il y a une seule del donc l'operande est ignore
					led.allumerRouge();
					break;
				
				case 0x45:
					//il y a une seule del donc l'operande est ignore
					led.eteindre();
					break;
				
				case 0x48:
					piezo.setFrequency(data[1]);
					piezo.start();
					break;
				
				case 0x09:
					piezo.stop();
					break;
				
				case 0x60:
					pwm.ajustementPWM(0,0,0,0);
					break;
					
				case 0x61:
					pwm.ajustementPWM(0,0,0,0);
					break;
				
				case 0x62:
					pwm.ajustementPWM(data[1]*100/255,data[1]*100/255,1, 1);
					break;
				
				case 0x63:
					pwm.ajustementPWM(data[1]*100/255,data[1]*100/255,0, 0);
					break;
				
				case 0x64:
					pwm.ajustementPWM(0,90,0,0);
					_delay_ms(1000);
					pwm.arretMoteur();
					break;
				
				case 0x65:
					pwm.ajustementPWM(100,0,0,0);
					_delay_ms(1040);
					pwm.arretMoteur();
					break;
				
				case 0xC0:
					base_pointer = i;
                    boucle_iter = data[1];
					break;
				
				case 0xC1:
					if (boucle_iter > 0) 
					{
                        boucle_iter--;
                        i = base_pointer;
                    }
					break;
				
				case 0xFF:
					finTrouve = true;
					piezo.stop();
					pwm.arretMoteur();
					break;
			}
			
		} else if ( data[0] == 0x01 ) 
		
		{
			dbtTrouve = true ;
		}
		
		i += 2;
	
}
	return 0;
}
