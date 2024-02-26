/* Name: main.c
 * Author: g.culotta *
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    //Setup
    DDRB |= (1 << 0) | (1 << 1) | (1 << 2);
    
    while(1){
        int i;
        for (i=0;i<3;i++){
        PORTB |= (1 << i);
        _delay_ms(50);
        PORTB &= ~(1 <<i);
        _delay_ms(50);
        }
    }
    return 0;   /* never reached */
}
