# MSP430
## basic1.c
This code creates a pattern where the red LED flashes on and off quickly, followed by the green LED turning on for a longer period.
It uses busy-wait loops with while(!(TA0CTL & TAIFG)) {} to wait for the timer to reach the desired state before proceeding. The Timer A0 interrupt flag (TAIFG) is checked to determine when the timer has reached its desired value.
## basic2.c

## basic3.c
