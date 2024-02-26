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
void left();
void right();

int main(void)
{
    
    DDRB |= (1 << PB6) | (1 << PB5) | (1 << PB4) | (1 << PB3) | (1 << PB2) | (1 << PB1) | (1 << PB0); //Setup as output
    DDRD |= 1 << PD6; //Setup as output
    
    DDRD &= ~(1 << PD5); //Setup as input
    PORTD |= (1 << PD5); //Enable pullup resistor
    
    DDRD &= ~(1 << PD4); //Setup as input
    PORTD |= (1 << PD4); //Enable pullup resistor
    
    DDRD &= ~(1 << PD3); //Setup as input
    PORTD |= (1 << PD3); //Enable pullup resistor
    
    DDRD &= ~(1 << PD2); //Setup as input
    PORTD |= (1 << PD2); //Enable pullup resistor
    
#define Ax_on  PORTB |= (1 <<  PB2);
#define Bx_on  PORTB |= (1 <<  PB1);
#define Cx_on  PORTB |= (1 <<  PB0);
#define Dx_on  PORTD |= (1 <<  PD6);
#define Ax_off  PORTB &= ~(1 <<  PB2);
#define Bx_off  PORTB &= ~(1 <<  PB1);
#define Cx_off  PORTB &= ~(1 <<  PB0);
#define Dx_off  PORTD &= ~(1 <<  PD6);

#define Ay_on  PORTB |= (1 <<  PB6);
#define By_on  PORTB |= (1 <<  PB5);
#define Cy_on  PORTB |= (1 <<  PB4);
#define Dy_on  PORTB |= (1 <<  PB3);
#define Ay_off  PORTB &= ~(1 <<  PB6);
#define By_off  PORTB &= ~(1 <<  PB5);
#define Cy_off  PORTB &= ~(1 <<  PB4);
#define Dy_off  PORTB &= ~(1 <<  PB3);
    
    while(1){
        if ((PIND & (1 << PD5)) == 0) {    // is switch closed?
            up();
        }
        if ((PIND & (1 << PD4)) == 0) {    // is switch closed?
            down();
        }
        if ((PIND & (1 << PD3)) == 0) {    // is switch closed?
            left();
        }
        if ((PIND & (1 << PD2)) == 0) {    // is switch closed?
            right();
        }
        //else reset..
        Ax_off;
        Ay_off;
        Bx_off;
        By_off;
        Cx_off;
        Cy_off;
        Dx_off;
        Dy_off;
    }
    
    return 0;
}

void myDelay(){
    _delay_ms(5);
}

void up(){
    Ax_on;
    Ay_on;
    myDelay();
    Ax_off;
    Ay_off;
    Bx_on;
    By_on;
    myDelay();
    Bx_off;
    By_off;
    Cx_on;
    Cy_on;
    myDelay();
    Cx_off;
    Cy_off;
    Dx_on;
    Dy_on;
    myDelay();
    Dx_off;
    Dy_off;
}

void down(){
    Dx_on;
    Dy_on;
    myDelay();
    Dx_off;
    Dy_off;
    Cx_on;
    Cy_on;
    myDelay();
    Cx_off;
    Cy_off;
    Bx_on;
    By_on;
    myDelay();
    Bx_off;
    By_off;
    Ax_on;
    Ay_on;
    myDelay();
    Ax_off;
    Ay_off;
}

void right(){
    Ax_on;
    Dy_on;
    myDelay();
    Ax_off;
    Dy_off;
    Bx_on;
    Cy_on;
    myDelay();
    Bx_off;
    Cy_off;
    Cx_on;
    By_on;
    myDelay();
    Cx_off;
    By_off;
    Dx_on;
    Ay_on;
    myDelay();
    Dx_off;
    Ay_off;
}

void left(){
    Dx_on;
    Ay_on;
    myDelay();
    Dx_off;
    Ay_off;
    Cx_on;
    By_on;
    myDelay();
    Cx_off;
    By_off;
    Bx_on;
    Cy_on;
    myDelay();
    Bx_off;
    Cy_off;
    Ax_on;
    Dy_on;
    myDelay();
    Ax_off;
    Dy_off;
}
