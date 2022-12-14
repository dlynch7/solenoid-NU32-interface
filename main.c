// C standard library #includes:
#include <stdio.h>

// Application-specific #includes:
#include "NU32.h"       // constants, funcs for startup and UART
#include "solenoid.h"	// solenoid driver library

#define MAX_MESSAGE_LENGTH 200

const char menu_str[] =	"\
\t0: Solenoid OFF\r\n\
\t1: Solenoid ON\r\n\
\t2: Reduced-current holding OFF\r\n\
\t3: Reduced-current holding ON\r\n\
\t4: Get hold-phase PWM duty cycle\r\n\
\t5: Set hold-phase PWM duty cycle\r\n\
\t6: Get peak-current duration\r\n\
\t7: Set peak-current duration\r\n";

int main(void) {
	char message[MAX_MESSAGE_LENGTH]; // for serial I/O
	uint8_t hold_duty_cycle = 100;
	uint16_t peak_duration_ms = 1E3;
  
	NU32_Startup(); // cache on, interrupts on, LED/button init, UART init
	NU32_WriteUART3("Initialized NU32.\r\n");
	
	init_solenoid();
	NU32_WriteUART3("Initialized solenoid interface.\r\n");

	while (1) {
		NU32_WriteUART3("\nEnter a single-digit menu option:\r\n");
		NU32_WriteUART3(menu_str);
		NU32_ReadUART3(message, MAX_MESSAGE_LENGTH);// get message from computer

		NU32_WriteUART3("Received ");
		NU32_WriteUART3(message);                   // send message back
		NU32_WriteUART3(" from user.\r\n");			// carriage return and newline
			
		switch (message[0]) {
			case '0': { // turn solenoid OFF
				toggle_solenoid(SOLENOID_OFF);
				NU32_WriteUART3("\tSolenoid OFF.\r\n");
				break;
			}
			case '1': { // turn solenoid ON
				toggle_solenoid(SOLENOID_ON);
				NU32_WriteUART3("\tSolenoid ON.\r\n");
				break;
			}
			case '2': { // disable reduced-current holding
				toggle_current_reduction(0);
				NU32_WriteUART3("\tReduced-current holding disabled.\r\n");
				break;
			}
			case '3': { // enable reduced-current holding
				toggle_current_reduction(1);
				NU32_WriteUART3("\tReduced-current holding enabled.\r\n");
				break;
			}
			case '4': { // get reduced-current PWM duty cycle
				sprintf(message,"\tHold-phase PWM duty cycle is %hu %%.\r\n",\
					get_hold_duty_cycle());
				NU32_WriteUART3(message);
				break;
			}
			case '5': { // set reduced-current PWM duty cycle
				NU32_WriteUART3("Enter hold-phase PWM duty cycle [integer, 0-100]:\r\n");
				NU32_ReadUART3(message,MAX_MESSAGE_LENGTH);
				sscanf(message,"%hhu",&hold_duty_cycle);
				set_hold_duty_cycle(hold_duty_cycle);
				sprintf(message,"\tSet hold-phase PWM duty cycle to %hhu %%.\r\n",\
					get_hold_duty_cycle());
				NU32_WriteUART3(message);
				break;
			}
			case '6': { // get peak-current duration
				sprintf(message,"\tPeak-current duration: %hu ms.\r\n",\
					get_peak_duration_ms());
				NU32_WriteUART3(message);
				break;
			}
			case '7': { // set peak-current duration
				NU32_WriteUART3("Enter peak-current duration [integer, milliseconds]:\r\n");
				NU32_ReadUART3(message,MAX_MESSAGE_LENGTH);
				sscanf(message,"%hu",&peak_duration_ms);
				set_peak_duration_ms(peak_duration_ms);
				sprintf(message,"\tSet peak-current duration to %hu ms.\r\n",\
					get_peak_duration_ms());
				NU32_WriteUART3(message);	
				break;
			}
			default: { // Unrecognized option, handle error
				NU32_WriteUART3("Unrecognized option.\r\n");
				break;
			}
		}
		
		NU32_LED1 = !NU32_LED1;                       // toggle the LEDs
		NU32_LED2 = !NU32_LED2;
	}
	return 0;
}
