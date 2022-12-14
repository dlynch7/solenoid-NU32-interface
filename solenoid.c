/******************************************************************************
 *      Software interface for basic solenoid driver circuit                  *
 *                                                                            *
 *		Circuit is built around a transistor (e.g., MOSFET or Darlington) 	  *
 *		placed between the solenoid and ground (i.e., low-side switch).		  *
 ******************************************************************************/

#include "solenoid.h"

#include "util.h"

#include <stdio.h>

/******************************************************************************
 *      QUASI-PRIVATE VARIABLES                                               *
 *****************************************************************************/
static volatile uint8_t  hold_duty_cycle = 100;
static volatile uint16_t peak_duration_ms = 1E3;
static volatile uint8_t  current_reduction = 0;

/******************************************************************************
 *		QUASI-PUBLIC VARIABLES												  *
 *****************************************************************************/

/******************************************************************************
 *		QUASI-PRIVATE FUNCTIONS												  *
 *****************************************************************************/

/******************************************************************************
 *		QUASI-PUBLIC FUNCTIONS												  *
 ******************************************************************************/
// initialize interface to solenoid driver circuit,
// using Timer 2 and Output Compare 1 to generate a PWM signal
// at 20 kHz and 25 % duty cycle
void init_solenoid(void) {
	T2CONbits.TCKPS = 2;	// Timer2 prescaler N=4 (1:4)
	PR2 = 999;				// period = (PR2+1) * N * 12.5 ns = 50 us, 20 kHz
	TMR2 = 0;				// initial TMR2 count is 0
	OC1CONbits.OCM = 0x6;	// PWM mode without fault pin; other OC1CON bits are defaults
	OC1RS = PR2 + 1;		// duty cycle = 0C1RS/(PR2+1) = 100%
	OC1R  = OC1RS;			// initialize before turning OC1 on; afterward it is read-only
	T2CONbits.ON = 1;		// turn on Timer2
	OC1CONbits.ON = 1;		// turn on OC1
}

// Turn solenoid OFF or ON
void toggle_solenoid(uint8_t off_or_on) {
	switch (off_or_on) {
		case SOLENOID_OFF: {
			OC1RS = 0; // 0% duty cycle --> solenoid is OFF
			break;
		}
		case SOLENOID_ON: {
			// set OC1RS to the fraction of (PR2 + 1) specified by the duty cycle
			if (current_reduction) {
				OC1RS = PR2 + 1;
				simple_delay_us(1E3*peak_duration_ms);
				OC1RS = ((int) ((hold_duty_cycle/100.0)*(PR2 + 1)));
			} else {
				OC1RS = PR2 + 1; // equivalent to 100% duty cycle
			}
		}
	}
}

// enable/disable hold-phase current reduction via PWM:
void toggle_current_reduction(uint8_t on_or_off) {
	current_reduction = on_or_off & 0x01; // ignore all but lsb
}

// get the peak current duration in milliseconds:
uint16_t get_peak_duration_ms(void) {
	return peak_duration_ms;
}

// set the peak current duration in milliseconds:
void set_peak_duration_ms(uint16_t duration_ms) {
	peak_duration_ms = duration_ms;
}

// get the hold-phase PWM duty cycle
uint8_t get_hold_duty_cycle(void) {
	return hold_duty_cycle;
}

// set the hold-phase PWM duty cyce
void set_hold_duty_cycle(uint8_t duty_cycle) {
	hold_duty_cycle = duty_cycle;
}
