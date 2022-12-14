/******************************************************************************
 *      Software interface for basic solenoid driver circuit                  *
 *                                                                            *
 *      Circuit is built around a transistor (e.g., MOSFET or Darlington)     *
 *      placed between the solenoid and ground (i.e., low-side switch).       *
 ******************************************************************************/
#ifndef SOLENOID__H__
#define SOLENOID__H__

#include "NU32.h"
#include <stdint.h>

#define SOLENOID_OFF	0
#define SOLENOID_ON 	1

// initialize interface between NU32 and solenoid driver circuit:
void init_solenoid(void);

// power the solenoid ON or OFF:
void toggle_solenoid(uint8_t);

// enable/disable hold-phase current reduction via PWM:
void toggle_current_reduction(uint8_t);

// get/set duration (milliseconds) of peak-current phase of solenoid actuation:
uint16_t get_peak_duration_ms(void);
void 	 set_peak_duration_ms(uint16_t);

// get/set PWM duty cycle during hold phase of solenoid actuation:
uint8_t get_hold_duty_cycle(void);
void 	set_hold_duty_cycle(uint8_t);


#endif // SOLENOID__H__
