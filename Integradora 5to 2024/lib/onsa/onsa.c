#include <onsa.h>
//----------------
#define BOT1 PC5
#define BOT2 PC4
#define BOT3 PC3
#define BOT4 PC2
#define BOT5 PC1
#define BOT6 PC0

//  no se usar bibliotecas XD, xd, enseñame Wels :)


/* el calculo es este brooooo::

*/
void setup_timer0()
{
    TCCR0A = 0b00000010; // Modo CTC
    TIMSK0 = 0b00000010; // Habilitar interrupción de comparación A
    OCR0A = 249;         // Valor de comparación
    TCCR0B = 0b00000011; // Prescaler 64
}

void config_io(void) // Implementación de la función config_io():
{
    DDRB |= ((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4)); // Configura PB0, PB1, PB3 y PB4 como salidas.
    DDRD |= ((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7)); // Configura PD2 a PD6 como salidas.

    // Configuración de pines de botones como entrada
    DDRC &= ~(1 << BOT1);
    DDRC &= ~(1 << BOT2);
    DDRC &= ~(1 << BOT3);
    DDRC &= ~(1 << BOT4);
    DDRC &= ~(1 << BOT5);
    DDRC &= ~(1 << BOT6);
    // Habilitar resistencias pull-up internas para los botones
    PORTC |= (1 << BOT1);
    PORTC |= (1 << BOT2);
    PORTC |= (1 << BOT3);
    PORTC |= (1 << BOT4);
    PORTC |= (1 << BOT5);
    PORTC |= (1 << BOT6);
}
