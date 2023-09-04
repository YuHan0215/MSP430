#include <msp430.h> 

#define btn_down 2

#define btn_up 1

#define B1 BIT3
/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= 0x41;        // Set as output 0100 0001
    P1REN |= B1;
    P1OUT |= B1;



    TA0CCR0 |= 5999;

    TA0CTL |= MC_1|ID_0|TASSEL_1|TACLR;  //up,/1,aclk,clear
    BCSCTL3 |= LFXT1S_2; //VLO as source

    volatile unsigned int state=1;  // prevent optimization
    volatile unsigned int led_state=1;  // prevent optimization

    for(;;) {






        if (state==1){

                if (led_state==1){
                    while(!(TA0CTL & TAIFG)) {}
                    P1OUT ^= 0x01;//red on
                    TA0CTL &= ~TAIFG;

                    led_state=2;

                }
                else if (led_state==2){
                    while(!(TA0CTL & TAIFG)) {}
                    P1OUT ^= 0x01;//red of
                    TA0CTL &= ~TAIFG;
                    led_state=3;
                }
                else if (led_state==3){
                    while(!(TA0CTL & TAIFG)) {}
                    P1OUT ^= 0x01;//red on
                    TA0CTL &= ~TAIFG;

                    led_state=4;
                }
                else if (led_state==4){
                    while(!(TA0CTL & TAIFG)) {}
                    P1OUT ^= 0x01;//red of
                    TA0CTL &= ~TAIFG;

                    led_state=5;
                }
                else if (led_state==5){
                    while(!(TA0CTL & TAIFG)) {}
                    P1OUT ^= 0x40;//g on
                    TA0CTL &= ~TAIFG;

                    TA0CCR0 = 10799;

                    led_state=6;

                }
                else if (led_state==6){
                    while(!(TA0CTL & TAIFG)) {}
                    P1OUT ^= 0x40;//g of
                    TA0CTL &= ~TAIFG;
                    TA0CCR0 = 5999;

                    led_state=1;
                }


                if ((P1IN & B1) == 0){
                     state = 2;

                     P1OUT &= ~0x41;
                     TA0CCR0 = 5999;
                }

        }

        else if (state==2){

            while(!(TA0CTL & TAIFG)) {}

            TA0CTL &= ~TAIFG;
            P1OUT ^= 0x41; //r g

            if((P1IN & B1) != 0){// up
                 state = 1;
                 P1OUT &= ~0x41;
                 TA0CCR0 = 5999;
                 led_state=1;
            }

        }


    }

}
