#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 4000000UL

void blink_01(void);
void blink_02(void);
int mode = 0;
void switchmode(void);


int main(void)
{
    // Set pins as OUT
    DDRD |= (1 << PD6);
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
    
    //Set pins as INPUT
    DDRB &= ~(1 << PB7);    // switch on pin PB7
    PORTB |= (1 << PB7);    // enable pull-up resistor
    
    while(1){
    
        if (PINB & (1 << PB7) && mode == 0) blink_01(); // is HIGH ??
        else if (PINB & (1 << PB7) && mode == 1) blink_02(); // is HIGH ??
        else switchmode();
        
        
    }
        
    return 0;
}


void switchmode(void){
    if (mode == 0) mode = 1;
    else mode = 0;
    _delay_ms(300);
    
}





void blink_01(void){
    
    
    PORTD |=  (1 << PD6);           // switch PD6 on
    _delay_ms(20);
    PORTD &= ~(1 << PD6);           // switch PD6 off
    _delay_ms(20);
    PORTB |=  (1 << PB0);
    _delay_ms(20);
    PORTB &= ~(1 << PB0);
    _delay_ms(20);
    PORTB |=  (1 << PB1);
    _delay_ms(20);
    PORTB &= ~(1 << PB1);
    _delay_ms(20);
    PORTB |=  (1 << PB2);
    _delay_ms(20);
    PORTB &= ~(1 << PB2);
    _delay_ms(20);
    PORTB |=  (1 << PB1);
    _delay_ms(20);
    PORTB &= ~(1 << PB1);
    _delay_ms(20);
    PORTB |=  (1 << PB0);
    _delay_ms(20);
    PORTB &= ~(1 << PB0);
    _delay_ms(20);
    
    
}

void blink_02(void){
    
    
    PORTD |=  (1 << PD6);           // switch on
    PORTB |=  (1 << PB0);
    PORTB |=  (1 << PB1);
    PORTB |=  (1 << PB2);
    _delay_ms(30);
    PORTD &= ~(1 << PD6);           // switch off
    PORTB &= ~(1 << PB0);
    PORTB &= ~(1 << PB1);
    PORTB &= ~(1 << PB2);
    _delay_ms(30);
    
    
}
