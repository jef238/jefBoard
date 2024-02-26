#define F_CPU 4000000UL  // 4 MHz
/**
 * Copyright (c) 2016, Łukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 * ATtiny13/007
 * Simple tone generator.
 * --
 * Settings:
 *  FUSE_L=0x6A
 *  FUSE_H=0xFF
 *  F_CPU=1200000
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

// Define baud rate
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


#define    N_1    (_BV(CS00))
#define    N_8    (_BV(CS01))
#define    N_64    (_BV(CS01)|_BV(CS00))
#define    N_256    (_BV(CS02))
#define    N_1024    (_BV(CS02)|_BV(CS00))



volatile unsigned char value;
/* This variable is volatile so both main and RX interrupt can use it.
 It could also be a uint8_t type */

/* Interrupt Service Routine for Receive Complete
 NOTE: vector name changes with different AVRs see AVRStudio -
 Help - AVR-Libc reference - Library Reference - <avr/interrupt.h>: Interrupts
 for vector names other than USART_RX_vect for Attiny2313 */



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



typedef struct s_note {
    uint8_t OCRxn; // 0..255
    uint8_t N;
} note_t;

typedef struct s_octave {
    note_t note_C;
    note_t note_CS;
    note_t note_D;
    note_t note_DS;
    note_t note_E;
    note_t note_F;
    note_t note_FS;
    note_t note_G;
    note_t note_GS;
    note_t note_A;
    note_t note_AS;
    note_t note_B;
} octave_t;

/*
 All calculations below are prepared for ATtiny13 default clock source (1.2MHz)
 F = F_CPU / (2 * N * (1 + OCRnx)), where:
 - F is a calculated PWM frequency
 - F_CPU is a clock source (1.2MHz)
 - the N variable represents the prescaler factor (1, 8, 64, 256, or 1024).
 */

PROGMEM const octave_t octaves[9] = {
    { // octave 0
        .note_C = {142, N_256}, // 16.35 Hz
        .note_CS = {134, N_256}, // 17.32 Hz
        .note_D = {127, N_256}, // 18.35 Hz
        .note_DS = {120, N_256}, // 19.45 Hz
        .note_E = {113, N_256}, // 20.60 Hz
        .note_F = {106, N_256}, // 21.83 Hz
        .note_FS = {100, N_256}, // 23.12 Hz
        .note_G = {95, N_256}, // 24.50 Hz
        .note_GS = {89, N_256}, // 25.96 Hz
        .note_A = {84, N_256}, // 27.50 Hz
        .note_AS = {79, N_256}, // 29.14 Hz
        .note_B = {75, N_256} // 30.87 Hz
    },
    { // octave 1
        .note_C = {71, N_256}, // 32.70 Hz
        .note_CS = {67, N_256}, // 34.65 Hz
        .note_D = {63, N_256}, // 36.71 Hz
        .note_DS = {59, N_256}, // 38.89 Hz
        .note_E = {56, N_256}, // 41.20 Hz
        .note_F = {53, N_256}, // 43.65 Hz
        .note_FS = {50, N_256}, // 46.25 Hz
        .note_G = {47, N_256}, // 49.00 Hz
        .note_GS = {44, N_256}, // 51.91 Hz
        .note_A = {42, N_256}, // 55.00 Hz
        .note_AS = {39, N_256}, // 58.27 Hz
        .note_B = {37, N_256} // 61.74 Hz
    },
    { // octave 2
        .note_C = {142, N_64}, // 65.41 Hz
        .note_CS = {134, N_64}, // 69.30 Hz
        .note_D = {127, N_64}, // 73.42 Hz
        .note_DS = {120, N_64}, // 77.78 Hz
        .note_E = {113, N_64}, // 82.41 Hz
        .note_F = {106, N_64}, // 87.31 Hz
        .note_FS = {100, N_64}, // 92.50 Hz
        .note_G = {95, N_64}, // 98.00 Hz
        .note_GS = {89, N_64}, // 103.83 Hz
        .note_A = {84, N_64}, // 110.00 Hz
        .note_AS = {79, N_64}, // 116.54 Hz
        .note_B = {75, N_64} // 123.47 Hz
    },
    { // octave 3
        .note_C = {71, N_64}, // 130.81 Hz
        .note_CS = {67, N_64}, // 138.59 Hz
        .note_D = {63, N_64}, // 146.83 Hz
        .note_DS = {59, N_64}, // 155.56 Hz
        .note_E = {56, N_64}, // 164.81 Hz
        .note_F = {53, N_64}, // 174.61 Hz
        .note_FS = {50, N_64}, // 185.00 Hz
        .note_G = {47, N_64}, // 196.00 Hz
        .note_GS = {44, N_64}, // 207.65 Hz
        .note_A = {42, N_64}, // 220.00 Hz
        .note_AS = {39, N_64}, // 233.08 Hz
        .note_B = {37, N_64} // 246.94 Hz
    },
    { // octave 4
        .note_C = {35, N_64}, // 261.63 Hz
        .note_CS = {33, N_64}, // 277.18 Hz
        .note_D = {31, N_64}, // 293.66 Hz
        .note_DS = {29, N_64}, // 311.13 Hz
        .note_E = {27, N_64}, // 329.63 Hz
        .note_F = {26, N_64}, // 349.23 Hz
        .note_FS = {24, N_64}, // 369.99 Hz
        .note_G = {23, N_64}, // 392.00 Hz
        .note_GS = {22, N_64}, // 415.30 Hz
        .note_A = {20, N_64}, // 440.00 Hz
        .note_AS = {19, N_64}, // 466.16 Hz
        .note_B = {18, N_64} // 493.88 Hz
    },
    {  // octave 5
        .note_C = {142, N_8}, // 523.25 Hz
        .note_CS = {134, N_8}, // 554.37 Hz
        .note_D = {127, N_8}, // 587.33 Hz
        .note_DS = {120, N_8}, // 622.25 Hz
        .note_E = {113, N_8}, // 659.25 Hz
        .note_F = {106, N_8}, // 349.23 Hz
        .note_FS = {100, N_8}, // 369.99 Hz
        .note_G = {95, N_8}, // 392.00 Hz
        .note_GS = {89, N_8}, // 415.30 Hz
        .note_A = {84, N_8}, // 440.00 Hz
        .note_AS = {79, N_8}, // 466.16 Hz
        .note_B = {75, N_8} // 493.88 Hz
    },
    {  // octave 6
        .note_C = {71, N_8}, // 1046.50 Hz
        .note_CS = {67, N_8}, // 1108.73 Hz
        .note_D = {63, N_8}, // 1174.66 Hz
        .note_DS = {59, N_8}, // 1244.51 Hz
        .note_E = {56, N_8}, // 1318.51 Hz
        .note_F = {53, N_8}, // 1396.91 Hz
        .note_FS = {50, N_8}, // 1479.98 Hz
        .note_G = {47, N_8}, // 1567.98 Hz
        .note_GS = {44, N_8}, // 1661.22 Hz
        .note_A = {42, N_8}, // 1760.00 Hz
        .note_AS = {39, N_8}, // 1864.66 Hz
        .note_B = {37, N_8} // 1975.53 Hz
    },
    {  // octave 7
        .note_C = {35, N_8}, // 2093.00 Hz
        .note_CS = {33, N_8}, // 2217.46 Hz
        .note_D = {31, N_8}, // 2349.32 Hz
        .note_DS = {29, N_8}, // 2489.02 Hz
        .note_E = {27, N_8}, // 2637.02 Hz
        .note_F = {26, N_8}, // 2793.83 Hz
        .note_FS = {24, N_8}, // 2959.96 Hz
        .note_G = {23, N_8}, // 3135.96 Hz
        .note_GS = {22, N_8}, // 3322.44 Hz
        .note_A = {20, N_8}, // 3520.00 Hz
        .note_AS = {19, N_8}, // 3729.31 Hz
        .note_B = {18, N_8} // 3951.07 Hz
    },
    {  // ultrasounds 8
        .note_C = {132, N_1}, // 15000 Hz
        .note_CS = {128, N_1}, // 15500 Hz
        .note_D = {124, N_1}, // 16000 Hz
        .note_DS = {120, N_1}, // 16500 Hz
        .note_E = {116, N_1}, // 17000 Hz
        .note_F = {113, N_1}, // 17500 Hz
        .note_FS = {110, N_1}, // 18000 Hz
        .note_G = {107, N_1}, // 18500 Hz
        .note_GS = {104, N_1}, // 19000 Hz
        .note_A = {101, N_1}, // 19500 Hz
        .note_AS = {99, N_1}, // 20000 Hz
        .note_B = {96, N_1} // 20500 Hz
    }
};


static void
tone(uint8_t octave, uint8_t note)
{
    uint32_t ret;
    note_t *val;
    ret = pgm_read_word_near((uint8_t *)&octaves + sizeof(octave_t) * octave + sizeof(note_t) * note);
    val = (note_t *)&ret;
    TCCR0B = (TCCR0B & ~((1<<CS02)|(1<<CS01)|(1<<CS00))) | val->N;
    OCR0A = val->OCRxn - 1; // set the OCRnx
}

static void
stop(void)
{
    TCCR0B &= ~((1<<CS02)|(1<<CS01)|(1<<CS00)); // stop the timer
    PORTD &= ~(1 <<  PD4); // turn off LED
}

static void
pause(int rnd)
{
    if (rnd == 1) _delay_ms(50);
    else if(rnd == 2) _delay_ms(300);
    else if(rnd == 3) _delay_ms(500);
    else if(rnd == 4) _delay_ms(750);
    else _delay_ms(1000);
}



int main(void)
{
    
    /* setup */
    
    USART_Init();  // Initialise USART
    sei();         // enable all interrupts
    
    DDRD &= ~(1 << PD5); //Setup as input
    PORTD |= (1 << PD5); //Enable pullup resistor
    DDRB |= (1 << PB2); // set BUZZER pin as OUTPUT
    DDRD |= (1 << PD4); // set up LED pin as OUTPUT
    PORTB = 0b00000000; // set all pins to LOW
    PORTD &= ~(1 <<  PD4); // set LED PIN low
    TCCR0A |= (1<<WGM01); // set timer mode to Fast PWM
    TCCR0A |= (1<<COM0A0); // connect PWM pin to Channel A of Timer0
    
    
    
    
    /* loop */
    while (1) {
        if (PIND & (1 << PD5)) {    // is switch open?
            // switch is open...
            
            stop();
            
            if (value == 0x75) {            //ASCII for 'u'  ultrasuono
                tone(8,random() % 12);
                PORTD |= (1 <<  PD4);
                pause(random() % 6);
            }
            if (value == 0x64) {            //ASCII for 'd'  demo
                tone(5,random() % 12);
                PORTD |= (1 <<  PD4);
                pause(random() % 6);
            }
            if (value == 0x73) stop();      //ASCII for 's'  stop
        }
        else {
            // switch is closed...
            PORTD |= (1 <<  PD4);
            tone(5,random() % 12);
            pause(random() % 6);
        }
    }
   
}
