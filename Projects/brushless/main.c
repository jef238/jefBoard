/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <util/delay.h>

void mydelay();
void up();
void down();

int main(void)
{
    //Setup
    DDRD &= ~(1 << PD6);  //switch ON PD6
    PORTD |= (1 << PD6);  //enable pullup resistor
    
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);  //output to brushless coil A,B,C
    
    #define A_on  PORTB |= (1 <<  PB0);
    #define B_on  PORTB |= (1 <<  PB1);
    #define C_on  PORTB |= (1 <<  PB2);
    #define A_off  PORTB &= ~(1 <<  PB0);
    #define B_off  PORTB &= ~(1 <<  PB1);
    #define C_off  PORTB &= ~(1 <<  PB2);
    
    
    
    while (1){
        up();
    }
    return 0;   /* never reached */
}

void mydelay(){
    _delay_ms(5);
}

void up(){
    A_on;
    B_on;
    C_off;
    mydelay();
    A_on;
    B_off;
    C_off;
    mydelay();
    A_on;
    B_off;
    C_on;
    mydelay();
    A_off;
    B_off;
    C_on;
    mydelay();
    A_off;
    B_on;
    C_on;
    mydelay();
    A_off;
    B_on;
    C_off;
    mydelay();
}

void down(){
    A_off;
    B_on;
    C_off;
    mydelay();
    A_off;
    B_on;
    C_on;
    mydelay();
    A_off;
    B_off;
    C_on;
    mydelay();
    A_on;
    B_off;
    C_on;
    mydelay();
    A_on;
    B_off;
    C_off;
    mydelay();
}
