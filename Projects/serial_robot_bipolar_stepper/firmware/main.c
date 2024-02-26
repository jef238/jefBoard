#define F_CPU 4000000UL  // 4 MHz

/*Very Important - change F_CPU to match target clock
 Note: default AVR CLKSEL is 1MHz internal RC
 This program transmits continously on USART. Interrupt is used for
 Receive charactor, which is then transmitted instead. LEDs are used
 as a test. Normal RX routine is included but not used.
 Change USART_BAUDRATE constant to change Baud Rate
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Define baud rate
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

volatile unsigned char value;
/* This variable is volatile so both main and RX interrupt can use it.
 It could also be a uint8_t type */

/* Interrupt Service Routine for Receive Complete
 NOTE: vector name changes with different AVRs see AVRStudio -
 Help - AVR-Libc reference - Library Reference - <avr/interrupt.h>: Interrupts
 for vector names other than USART_RX_vect for Attiny2313 */


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

void myDelay();
void up();
void down();
void left();
void right();
void stop();


void USART_Init(void){
    // Set baud rate
    UBRRL = BAUD_PRESCALE;// Load lower 8-bits into the low byte of the UBRR register
    UBRRH = (BAUD_PRESCALE >> 8);
    /* Load upper 8-bits into the high byte of the UBRR register
     Default frame format is 8 data bits, no parity, 1 stop bit
     to change use UCSRC, see AVR datasheet*/
    
    // Enable receiver and transmitter and receive complete interrupt
    UCSRB = ((1<<TXEN)|(1<<RXEN) | (1<<RXCIE));
}


void USART_SendByte(uint8_t u8Data){
    
    // Wait until last byte has been transmitted
    while((UCSRA &(1<<UDRE)) == 0);
    
    // Transmit data
    UDR = u8Data;
}


// not being used but here for completeness
// Wait until a byte has been received and return received data
uint8_t USART_ReceiveByte(){
    while((UCSRA &(1<<RXC)) == 0);
    return UDR;
}

ISR(USART_RX_vect){
   if (UDR != 0x0A) value = UDR;        //read UART register into value except <RETURN> key
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

void left(){
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

void stop(){
    Ax_off;
    Ay_off;
    Bx_off;
    By_off;
    Cx_off;
    Cy_off;
    Dx_off;
    Dy_off;
}

int main(void)
{
    
    DDRB |= (1 << PB6) | (1 << PB5) | (1 << PB4) | (1 << PB3) | (1 << PB2) | (1 << PB1) | (1 << PB0); //Setup as output
    DDRD |= 1 << PD6; //Setup as output
    
    

 
USART_Init();  // Initialise USART
sei();         // enable all interrupts
    
    while(1){
        if (value == 0x75) up();        //ASCII for 'u'
        if (value == 0x64) down();      //ASCII for 'd'
        if (value == 0x6C) left();      //ASCII for 'l'
        if (value == 0x72) right();     //ASCII for 'r'
        if (value == 0x73) stop();      //ASCII for 's'
    }
    
    return 0;
}
