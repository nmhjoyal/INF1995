#include "../../tp8/lib/del.cpp"
#include "../../tp8/lib/constantes.h"
#include "../../tp8/lib/memoire_24.h"
#include "../../tp8/lib/communicationUART.h"
#include "../../tp8/lib/pwm.h"
#include "Piezoelectrique.h"
#include <stdio.h>

#include <util/delay.h>

#define NOMBRE_INSTRUCTIONS 30
    
int main()
{ 
	del led;
	communicationUART uart;
	Memoire24CXXX memoire;
	
	uint16_t base_pointer = 0;
	uint8_t boucle_iter = 0;

	bool dbtTrouve = false;
	bool finTrouve = false;

	uint16_t i = 0;
	
	pwm pwm; 
	Piezoelectrique piezo;
	


	
	pwm.arretMoteur();
	while (i < NOMBRE_INSTRUCTIONS && !finTrouve)
	{
		uint8_t data[2];
		memoire.lecture(i, data, 2);
		
		if (dbtTrouve)
		{
			switch(data[0]) 
			{
				case 0x02:
					_delay_ms(2500);
					break;
				
				case 0x44:
					led.allumerRouge(); 
					break;
				
				case 0x45:
					led.eteindre();
					break;
				
				case 0x48:
					piezo.setFrequency(data[1]);
					piezo.start();
					break;
				
				case 0x09:
					piezo.stop();
					break;
				
				case 0x60 || 0x61:
					pwm.arretMoteur();
					break;
				
				case 0x62:
					pwm.ajustementPWM(data[1]/255*100,data[1]/255*100,0, 0);
					break;
				
				case 0x63:
					pwm.ajustementPWM(data[1]/255*100,data[1]/255*100,1, 1);
					break;
				
				case 0x64:
					pwm.ajustementPWM(0,data[1]/255*100,1, 1);
					_delay_ms(270);
					pwm.arretMoteur();
					break;
				
				case 0x65:
					pwm.ajustementPWM(data[1]/255*100,0,1, 1);
					_delay_ms(270);
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
