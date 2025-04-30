#define F_CPU 16000000UL  
#include <avr/io.h>  
#include <util/delay.h>

int main(void) {
    DDRD |= 0xF0;     // columnas salida
    DDRD &= ~0x0F;    // Filas como entrada
    PORTD |= 0x0F;    // en up fila

    DDRB|= 0x0F;     // LEds que muestran valores correctos
    DDRB|=0X30;//LED VERDE ROJO

    DDRC|=0X03;//MOTOR

    char filas;
    char secuencia=0;

    while (1) {
        PORTD |= 0xF0;    // Todas las columnas en high
        PORTD &= ~0x10;   // Activar solo columna 0 (PD4 en LOW)
        _delay_us(5);     // 
        filas = PIND & 0x0F; // Leemos solo las filas (PD0–PD3)
        PORTB|= 0X20; //prendemosled verde

        switch (filas) {
            case 0x0E: // fila 1
            if(secuencia==0){    
              PORTB = 0x01; // Enciende LED
                secuencia=1;
            }
                break;

            case 0x0D: // fila 2
            if(secuencia==1){ 
                PORTB = 0x02; // 
                secuencia=2;
            }
                break;

            case 0x0B: // fila 3
            if(secuencia==2){ 
            PORTB = 0x04;
                secuencia=3;
            }
                break;

            case 0x07: //fila 4
            if(secuencia==3){     
            PORTB = 0x08;
                secuencia=4;
            }
                break;
        }

        PORTD |= 0xF0;
        PORTD &= ~0x20;   // tivar columna 2 
        _delay_us(5);
        filas = PIND & 0x0F;

        if (filas == 0x0E) { // fila 1 presionada
            if (secuencia == 4) {
                PORTB|= 0X20; // LED correcto ON
                PORTC=0X01;//motor
                _delay_ms(3000);
                PORTB&=~0X0F;//apago los leds
                PORTC&= ~0x01;//apago motor
                secuencia=0;
            } else {
                PORTB |= 0X10; // LED error ON
                PORTB&=~ 0x20; //
                _delay_ms(1000);
                PORTB &= ~0X10; //apagoled
                PORTB&=~(0X0F);//APAGAR LEDS
                _delay_ms(100);
                secuencia = 0;
            }
        }
      }
    }
