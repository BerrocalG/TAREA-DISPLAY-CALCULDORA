/*#define F_CPU 16000000UL  
#include <avr/io.h>  
#include <util/delay.h>

int main(void) {
  DDRD|=0xF0; //matrizcolumna
  DDRD&= ~0X0F; //matriz fila

  DDRB|=0X0F; //codificador
  DDRC|=0X07; //A0 A1 A2 display
  DDRC|=0X08; //A3 led

  char cuenta=0;
  char boton= 0;

  while(1){
  
  }

}
*/
/*
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= 0x0F;   // decodificador
    DDRC |= 0x07;   // prendido apagado display

    DDRD &=~ 0x0F;  // fila salidas
    DDRD|=0XF0;     // colunas entrada


    //PORTC|=0X07;

    char cuenta = 0;
    char pulsadores = 0;

    while (1) {

        PORTD |=0X0F;
        PORTC &= ~0x01;     // par apagar el display de decenas
        PORTC |= 0x02;      // para prender el display de unidades
        PORTB = (PORTB & 0x0F) | ((cuenta % 10) << 4);  // para "desplazar" las unidades a losp ines del deco
        _delay_ms(8); //display

        // Mostrar decenas
        PORTC &= ~0x02;     // para apagar el display de unidades
        PORTC |= 0x01;      // para prender e display de decenas
        PORTB = (PORTB & 0x0F) | ((cuenta / 10) << 4);  // para desplazar las decenas a los pines del deco
        _delay_ms(8);

        // Leer botones
        PORTD|=0XF0;
        PORTD&=~0X10;
        pulsadores= (!(PIND & 0XF0)|(0x0F));

        switch(pulsadores){

        case 0x10:
        cuenta=1;
        _delay_ms(100);
        break;

    }
    }
  }
*/
/*
        if (pulsadores == 0XE1) {  // boton para subir
         
            cuenta++; //aumenta 1 unidad
            if (cuenta > 99)
            cuenta = 99; //la suma no va sobre pasar los 99
            _delay_ms(200);//boton


        } else if (pulsadores == 0x21) {  // boton para bajar
            if (cuenta > 0)
            cuenta--;
            _delay_ms(200);
        }
    }
    */
//tarea contraseña completa

#define F_CPU 16000000UL  
#include <avr/io.h>  
#include <util/delay.h>

int main(void) {
    DDRD |= 0xF0;     // columnas salida
    DDRD &= ~0x0F;    // Filas como entrada
    PORTD |= 0x0F;    // en up fila

    DDRB |= 0x0F;     // LEds que muestran valores correctos
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

        

