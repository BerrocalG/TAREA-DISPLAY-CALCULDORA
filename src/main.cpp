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
#define F_CPU 16000000UL  
#include <avr/io.h>  
#include <util/delay.h>

int main(void) {
    DDRD |= 0xF0;     // Columnas (PD4–PD7) como salida
    DDRD &= ~0x0F;    // Filas (PD0–PD3) como entrada
    PORTD |= 0x0F;    // Pull-up activado en filas

    DDRB |= 0x0F;     // LED en PB0 como salida
    DDRB|=0X30;//LED VERDE ROJO


    char filas;
    char secuencia=0;

    while (1) {
        PORTD |= 0xF0;    // Todas las columnas en HIGH
        PORTD &= ~0x10;   // Activar solo columna 0 (PD4 en LOW)
        _delay_us(5);     // Estabilización
        filas = PIND & 0x0F; // Leemos solo las filas (PD0–PD3)
        
        switch (filas) {
            case 0x0E: // fila 1
            if(secuencia==0){    
              PORTB = 0x01; // Enciende LED
                secuencia=1;
            }
                break;

            case 0x0D: // fila 1
            if(secuencia==1){ 
                PORTB = 0x02; // 
                secuencia=2;
            }
                break;

            case 0x0B: // fila 1
            if(secuencia==2){ 
            PORTB = 0x04;
                secuencia=3;
            }
                break;

            case 0x07: //fila1 
            if(secuencia==3){     
            PORTB = 0x08;
                secuencia=4;
            }
                break;
        }
        
        _delay_ms(50); // Antirebote
    }
}
