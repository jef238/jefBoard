/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <util/delay.h>

void myDelay();
void up();
void down();

int main(void)
{

    DDRB |= (1 << PB2) | (1 << PB1) | (1 << PB0); //Setup as output
    DDRD |= 1 << PD6; //Setup as output
    
    DDRD &= ~(1 << PD5); //Setup as input
    PORTD |= (1 << PD5); //Enable pullup resistor
    
    #define A_on  PORTB |= (1 <<  PB2);
    #define B_on  PORTB |= (1 <<  PB1);
    #define C_on  PORTB |= (1 <<  PB0);
    #define D_on  PORTD |= (1 <<  PD6);
    #define A_off  PORTB &= ~(1 <<  PB2);
    #define B_off  PORTB &= ~(1 <<  PB1);
    #define C_off  PORTB &= ~(1 <<  PB0);
    #define D_off  PORTD &= ~(1 <<  PD6);
    

    while(1){
        if (PIND & (1 << PD5)) {    // is switch open?
            // switch is open...
            up();
        }
        else {
            // switch is closed...
            up();
        }
    }
    
    return 0;
}

void myDelay(){
    _delay_ms(5);
}

void up(){
    A_on;
    B_on;
    myDelay();
    A_off;
    B_on;
    C_on;
    myDelay();
    B_off;
    C_on;
    D_on;
    myDelay();
    C_off;
    D_on;
    A_on;
    myDelay();
    D_off;
    A_off;
}
void up1(){
    A_on;
    myDelay();
    A_off;
    B_on;
    myDelay();
    B_off;
    C_on;
    myDelay();
    C_off;
    D_on;
    myDelay();
    D_off;
}

