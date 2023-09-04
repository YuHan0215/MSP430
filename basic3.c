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

    TA1CCR0 |= 34374;
    TA1CTL |= MC_1|ID_3|TASSEL_2|TACLR;  //up,/8,smclk,clear
    BCSCTL2 |= DIVS_3;  //DCL /8

    volatile unsigned int state=1;  // prevent optimization
    volatile unsigned int led_state=1;  // prevent optimization
    volatile unsigned int botn_down=0;  // prevent optimization

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

                 TA1CTL |= TACLR;
            }

        }

        if((P1IN & B1) == 0 ){
                          if (!botn_down){
                               botn_down=1;
                               TA1CTL |= TACLR;
                           }
                    }else if((P1IN & B1) != 0){
                          botn_down=0;
                          TA1CTL |= TACLR;
                    }
                    if (botn_down & (TA1CTL & TAIFG)){
                         TA1CTL &= ~TAIFG;

                         state = 2;

                         P1OUT &= ~0x41;
                         TA0CCR0 = 5999;


                         botn_down=0;
                     }


    }

}
