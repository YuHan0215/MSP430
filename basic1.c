#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= 0x41;        // Set as output 0100 0001

    TA0CCR0 |= 5999;

    TA0CTL |= MC_1|ID_0|TASSEL_1|TACLR;  //up,/1,aclk,clear
    BCSCTL3 |= LFXT1S_2; //VLO as source

    //volatile unsigned int stage=0;  // prevent optimization

    for(;;) {
        P1OUT &= ~0x41;
        while(!(TA0CTL & TAIFG)) {}
        P1OUT ^= 0x01;//red on
        TA0CTL &= ~TAIFG;

        while(!(TA0CTL & TAIFG)) {}
        P1OUT ^= 0x01;//red of
        TA0CTL &= ~TAIFG;

        while(!(TA0CTL & TAIFG)) {}
        P1OUT ^= 0x01;//red on
        TA0CTL &= ~TAIFG;

        while(!(TA0CTL & TAIFG)) {}
        P1OUT ^= 0x01;//red of
        TA0CTL &= ~TAIFG;


        while(!(TA0CTL & TAIFG)) {}
        P1OUT ^= 0x40;//g on
        TA0CTL &= ~TAIFG;

        TA0CCR0 = 10799;
        while(!(TA0CTL & TAIFG)) {}
        P1OUT ^= 0x40;//g of
        TA0CTL &= ~TAIFG;

        TA0CCR0 = 5999;
    }

}
