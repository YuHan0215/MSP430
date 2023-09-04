# MSP430
The code you provided is written for the MSP430 microcontroller using the Code Composer Studio IDE and is designed to control two LEDs (red and green) connected to pins P1.0 and P1.6. 
## basic1.c
This code creates a pattern where the red LED flashes on and off quickly, followed by the green LED turning on for a longer period.
It uses busy-wait loops with while(!(TA0CTL & TAIFG)) {} to wait for the timer to reach the desired state before proceeding. The Timer A0 interrupt flag (TAIFG) is checked to determine when the timer has reached its desired value.
## basic2.c
The code is similar to the previous code, but it includes additional functionality for handling a button press. 
state 1: The LEDs follow a sequence (red on, red off, green on, green off) controlled by led_state. If the button is pressed, it transitions to state 2.
state 2: The LEDs alternate between red and green. If the button is pressed again, it transitions back to state 1.
## basic3.c
This code incorporates additional functionality to handle a button press and debounce the button. It uses Timer A1 to debounce the button press before transitioning between states.
