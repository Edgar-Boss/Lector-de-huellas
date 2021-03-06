#include <16F876a.h>

#fuses XT,PUT,NOPROTECT,BROWNOUT,NOLVP,NOWDT
#use delay (clock=4000000)                      

#use i2c(MASTER, SDA=PIN_C4, SLOW, SCL=PIN_C3, NOFORCE_SW)

#define use_portb_kbd TRUE       //Configuración puerto b para lectura teclado
#include <kbd.c>                 //Carga archivo para control de teclado

#use standard_io(b)
#use standard_io(c)

int tecla;                       //Dato a transmitir
   

    
void envio_I2C (){
   
      i2c_start();         //Comienzo de la comunicación I2C ...
      i2c_write(0xa0);     //...con la dirección del PIC esclavo...
      i2c_write(tecla);    // Envia dato
      i2c_stop();          //Finalización de la transmisión
  }


void main(){
   kbd_init();                   //Inicializa función de teclado
   port_b_pullups(TRUE);         
    
   while (true){
      
// Lectura del teclado     
      tecla=kbd_getc();       //En "tecla" valor de la tecla pulsada
      if(tecla!=0){           //Si se pulsa teclado...
            envio_I2C();      //...se envía el dato
            delay_ms(100);
      }
   }
}
      


       
   


   
      
   
   

