#include <16F876a.h>

#fuses XT,PUT,NOPROTECT,BROWNOUT,NOLVP,NOWDT
#use delay (clock=4000000)                      

#use i2c(MASTER, SDA=PIN_C4, SLOW, SCL=PIN_C3, NOFORCE_SW)

#define use_portb_kbd TRUE       //Configuraci�n puerto b para lectura teclado
#include <kbd.c>                 //Carga archivo para control de teclado

#use standard_io(b)
#use standard_io(c)

int tecla;                       //Dato a transmitir
   

    
void envio_I2C (){
   
      i2c_start();         //Comienzo de la comunicaci�n I2C ...
      i2c_write(0xa0);     //...con la direcci�n del PIC esclavo...
      i2c_write(tecla);    // Envia dato
      i2c_stop();          //Finalizaci�n de la transmisi�n
  }


void main(){
   kbd_init();                   //Inicializa funci�n de teclado
   port_b_pullups(TRUE);         
    
   while (true){
      
// Lectura del teclado     
      tecla=kbd_getc();       //En "tecla" valor de la tecla pulsada
      if(tecla!=0){           //Si se pulsa teclado...
            envio_I2C();      //...se env�a el dato
            delay_ms(100);
      }
   }
}
      


       
   


   
      
   
   
