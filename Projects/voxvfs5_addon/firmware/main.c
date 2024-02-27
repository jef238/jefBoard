/* Name: main.c
 * Author: Giuseppe Culotta
 */

#include <avr/io.h>
#include <util/delay.h>

void blink_01(void);
void channel_1(void);
void channel_2(void);
void channel_3(void);
void channel_4(void);


int main(void)
{
    // Set pins as OUT
    DDRD |= (1 << PD6);
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
    
    //Set pins as INPUT
    DDRD &= ~(1 << PD5) | ~(1 << PD4) | ~(1 << PD3) | ~(1 << PD2); // switch on pin PD5-2
    PORTD |= (1 << PD5) | (1 << PD4) | (1 << PD3) | (1 << PD2);    // enable pull-up resistor
    
    blink_01();
    
    while(1){
        if (PIND & (1 << PD5)) channel_1();
        if (PIND & (1 << PD4)) channel_2();
        if (PIND & (1 << PD3)) channel_3();
        if (PIND & (1 << PD2)) channel_4();
    }
    return 0;
}


void channel_1(void){
    PORTD |=  (1 << PD6);
    PORTB &= ~(1 << PB0);
    PORTB &= ~(1 << PB1);
    PORTB &= ~(1 << PB2);
}

void channel_2(void){
    PORTD &= ~(1 << PD6);
    PORTB |=  (1 << PB0);
    PORTB &= ~(1 << PB1);
    PORTB &= ~(1 << PB2);
}

void channel_3(void){
    PORTD &= ~(1 << PD6);
    PORTB &= ~(1 << PB0);
    PORTB |=  (1 << PB1);
    PORTB &= ~(1 << PB2);
}

void channel_4(void){
    PORTD &= ~(1 << PD6);
    PORTB &= ~(1 << PB0);
    PORTB &= ~(1 << PB1);
    PORTB |=  (1 << PB2);
}

void blink_01(void){
    
    PORTD |=  (1 << PD6);
    _delay_ms(40);
    PORTD &= ~(1 << PD6);
    _delay_ms(40);
    PORTB |=  (1 << PB0);
    _delay_ms(40);
    PORTB &= ~(1 << PB0);
    _delay_ms(40);
    PORTB |=  (1 << PB1);
    _delay_ms(40);
    PORTB &= ~(1 << PB1);
    _delay_ms(40);
    PORTB |=  (1 << PB2);
    _delay_ms(40);
    PORTB &= ~(1 << PB2);
    _delay_ms(40);
    PORTB |=  (1 << PB1);
    _delay_ms(40);
    PORTB &= ~(1 << PB1);
    _delay_ms(40);
    PORTB |=  (1 << PB0);
    _delay_ms(40);
    PORTB &= ~(1 << PB0);
    _delay_ms(40);
    PORTD |=  (1 << PD6);
    _delay_ms(40);
    PORTD &= ~(1 << PD6);
    _delay_ms(40);
    
}
