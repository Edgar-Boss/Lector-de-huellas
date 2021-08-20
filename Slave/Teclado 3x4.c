//*****************************************************************************
// El lcd esta conectado en el puerto D, el teclado en el puerto B
// Drive de teclaDO KBD.C PARA TECLADO DE 3X4
// JUN16
//*****************************************************************************
#include <16F877.h>
#fuses xt,nowdt,noprotect,nolvp
#use delay(clock= 12M)
#include <lcd.c>
#include <kbd_4x4.c>
//#include <KBD.c>

void main() 
{   

char k;
int x;
lcd_init();
kbd_init();
port_b_pullups(TRUE);
lcd_putc("\f Da una Tecla...\n");

   while (TRUE)
   {
   

   k=kbd_getc();
   x=k-48;
   if(k!=0)
      {
         if(k=='*')
          lcd_putc('\f');
         else
          
            printf(lcd_putc, "\f Caracter=%c",k);
              delay_ms(1000);
         
            printf(lcd_putc, " \f Car=%u",k);
            printf(lcd_putc, "  Num=%u",x);
            delay_ms(1000);
             
            lcd_putc("\f Da una Tecla...\n");

   
      }//if k  

    }//while  
}


