//************************************************************************************************
// Lee un nunero de un teclado  4x4  conectado al puerto B y lo muestra en el LCD conectado al puerto D
// Drive para teclado  4x4 
// Para simular en proteus usar resistencias externas.
//JUN 16,oct16
//***********CONFIGURACION DEL PIC ************************************************************************

#include <18f4550.h>
                                    
#fuses HS,NOWDT,NOPROTECT,NOLVP,PUT,CPUDIV1,BROWNOUT    // Palabra de Configuración
#fuses NOPBADEN                  //configura  I/O digitales.
#use delay(clock=20M)                           //Velocidad del reloj externo, 12 mhz

#include <lcd.c>                  //  Display

#include <kbd_4x4.c>             //Libreria para el manejo de un Teclado 4x4


//#define use_portb_kbd TRUE     // Puerto B  a utilizar para el Teclado Matricial
#define use_portd_lcd TRUE     // Puerto D  a utilizar para el LCD

//************************  PROGRAMA  ************************

void main()
{   

char k;
int x;
lcd_init();
kbd_init();

port_b_pullups(TRUE);
lcd_putc("\f Da una Tecla..\n");

   while (TRUE)
   {
  
   k=kbd_getc();

   if(k!=0)
      {
         if(k=='*')
          lcd_putc('\f');
         else
          
            printf(lcd_putc, "\f Caracter=%c",k);
            delay_ms(300);
             
      }//if k  

    }//while  
}



