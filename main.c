// C standard library #includes:
#include <stdio.h>

// Application-specific #includes:
#include "NU32.h"       // constants, funcs for startup and UART
#include "solenoid.h"	// solenoid driver library

#define MAX_MESSAGE_LENGTH 200

const char menu_str[] =	"\
\t0: \r\n\
\t1: \r\n\
\t2: \r\n\
\t3: \r\n\
\t4: \r\n\
\t5: \r\n\
\t6: \r\n\
\t7: \r\n\
\t8: \r\n\
\t9: \r\n";

int main(void) {
	char message[MAX_MESSAGE_LENGTH]; // for serial I/O
  
	NU32_Startup(); // cache on, interrupts on, LED/button init, UART init
	NU32_WriteUART3("Initialized NU32.\r\n");
	
	// TODO: initialize solenoid interface
	NU32_WriteUART3("Initialized solenoid interface.\r\n");

	while (1) {
		NU32_WriteUART3("\nEnter a single-digit menu option:\r\n");
		NU32_WriteUART3(menu_str);
		NU32_ReadUART3(message, MAX_MESSAGE_LENGTH);// get message from computer

		NU32_WriteUART3("Received ");
		NU32_WriteUART3(message);                   // send message back
		NU32_WriteUART3(" from user.\r\n");			// carriage return and newline
			
		switch (message[0]) {
			case '0': { // TODO
				// NU32_WriteUART3(".\r\n"); // TODO
				break;
			}
			case '1': { // enable/disable motor
				// NU32_WriteUART3(".\r\n"); // TODO
				break;
			}
			case '2': { // TODO
				// NU32_WriteUART3(".\r\n"); // TODO
				break;
			}
			case '3': { // TODO
				// NU32_WriteUART3(".\r\n"); // TODO
				break;
			}
			case '4': { // TODO
				// NU32_WriteUART3(".\r\n"); // TODO
				break;
			}
			case '5': { // TODO
				// NU32_WriteUART3(".\r\n"); // TODO
				break;
			}
			case '6': { // TODO
				// NU32_WriteUART3(".\r\n"); // TODO
				break;
			}
			case '7': { // TODO
				// NU32_WriteUART3(".\r\n"); // TODO
				break;
			}
			case '8': { // TODO
				// NU32_WriteUART3(".\r\n"); // TODO
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
