# solenoid-NU32-interface
Basic interface between NU32 devboard and solenoid driver circuit

## Description
This project implements a simple interface with a solenoid driver circuit built around a transistor (e.g., MOSFET or Darlington) placed between the solenoid and ground (i.e., low-side switch).

This project assumes a monostable solenoid, where current must flow to hold the solenoid in its extended position, and where a spring returns the solenoid to its rest position when current is removed.

The following features are exposed:
* engage/disengage solenoid
* switch between constant current profile and efficient current profile
* set/get PWM duty cycle (0-100) applied during reduced-current phase, when efficient current profile is enabled.
* set/get peak current duration: full current (100% duty cycle) is applied to the solenoid for this time before switching to the reduced-current PWM duty cycle.

## Project Structure
This project contains the following C and header files:
* `main.c`: the program entry point; implements user interface via switch statement inside an infinite while loop
* `solenoid.{c.h}`: contains functions to interact with the solenoid driver circuit
* `util.{c,h}`: contains helpful functions whose use can extend beyond any single library
* `NU32.{c,h}`: the NU32 library (see [http://hades.mech.northwestern.edu/index.php/NU32_Software](http://hades.mech.northwestern.edu/index.php/NU32_Software))

## Theoretical Background
The original purpose for developing this project was to help experimentally characterize a solenoid's holding force as a function of current.
Theoretically, the current required to hold solenoid in the "on" position is less than the initial current required to move the solenoid from the "off" position to the "on position.

For a solenoid, the electromotive force (EMF) is described by the Lorentz equation:
	F = BIL
where
* F is the holding force,
* B is the flux density of the magnetic field,
* I is the current, and
* L is the length of the conductor in the magnetic field.

The magnetic field strength is, in turn, given by
	B = uInL,
where
* u is the permeability of free space,
* I is the current through the solenoid coil
* n is the number of coil turns per unit length (e.g., meter), and
* L is the length of the conductor (coil)

The current through the coil, I, is given by Ohm's law: I = V/R, where V is the voltage across the oil and R is the coil resistance.

Thus, the EMF is given by
	F = un(L^2)(V^2)/(R^2)

As the coil (conductor) heats up, its resistence increases, so the current through the coil decreases for a given voltage drop across the coil, and as a result, the electromotive force F also decreases.

If the force required to maintain the solenoid in the "on" position is less than the force required to move the solenoid from the "off" position to the "on" position, there is no reason to apply the pull-in voltage V once the solenoid is in the "on" position; voltage can be lowered, reducing the current through the coil but also slowing the increase in resistance.
This voltage reduction can be achieved digitally by PWMing the voltage across the solenoid.
