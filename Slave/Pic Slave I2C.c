#include <16F876a.h>
#define use_portb_kbd TRUE    
#include<kbd.c>
#include <lcd.c>
#fuses XT
#use delay (clock=4000000)
#use standard_io(b)
#use standard_io(c)
#use standard_io(a)
#use I2C(SLAVE, SDA=PIN_C4 ,SLOW, SCL=PIN_C3, ADDRESS=0xa0, NOFORCE_SW)



void main() 
{

   output_a(0b11111111);
   
   char dato;
   int ban=0;
   int exit=0;
   char finger[5][5];
   char aux[2][8];
   int indx=0;
   int indy=0;
   lcd_init();
  
   
   while(true)//while principal
   {
      printf(lcd_putc,"\f");
      printf(lcd_putc,"Ingrese una");
      lcd_gotoxy(2,2);
      printf(lcd_putc,"opcion");
            
      while (exit==0)//para esperar pulsador
      {
         if(input(pin_a0))
         {
            ban=1;
            exit=1;
         }
         if(input(pin_a1))
         {
            ban=2;
            exit=1;
         }
   
      }//while  
      exit=0;
      printf(lcd_putc,"\f");
  
  if(ban==1 && indx>4)
  {
      printf(lcd_putc,"\f");
      printf(lcd_putc,"Slots llenos");
      delay_ms(1000);
      ban=0;
   }
  if(ban==1)
  {
      
      while(ban==1)//registro
      {
         printf(lcd_putc,"\f");
         printf(lcd_putc,"Coloque su dedo");
    
         lcd_gotoxy(2,2);
         exit=0;
         while(indy<4)//ingresar digitos
         {
         
            if(i2c_poll()) 
            {
               dato=i2c_read();
               if(dato=='*')
                  exit=1;
               else if(dato=='1'||dato=='2'||dato=='3'||dato=='4'||dato=='5'||dato=='6'||dato=='7'||dato=='8'||dato=='9'||dato=='0')
               {
                  aux[0][indy]=dato;
                  //printf(lcd_putc,"\f");
                  lcd_gotoxy(2,2);
                  printf(lcd_putc,"slot %d: ",indx+1);
                  lcd_gotoxy(indy+10,2);
               
                  printf(lcd_putc,"%c",dato);
                  indy++;
               
            }
                              //Muestra dato recibido por pantalla
         }
         
      
      }
      printf(lcd_putc,"\f");
      printf(lcd_putc,"Nuevamente");
      //delay_ms(500);
      
      lcd_gotoxy(2,2);
      
      indy=0;
      exit=0;
      while(indy<4)//ingresar digitos nuevaente
      {
         
         if(i2c_poll()) 
         {
            dato=i2c_read();
            if(dato=='*')
               exit=1;
            else if(dato=='1'||dato=='2'||dato=='3'||dato=='4'||dato=='5'||dato=='6'||dato=='7'||dato=='8'||dato=='9'||dato=='0')
            {
               finger[indx][indy]=aux[1][indy]=dato;
               indy++;
               lcd_putc(dato);
            }
                              //Muestra dato recibido por pantalla
         }
         
        
         
      }//while nuevamente
      
      //////comprobar que esta bien escrito 
        int comp=0;
         for(int k=0;k<4;k++)
         {
            if(aux[0][k]!=aux[1][k])
               comp++;
         }
         if(comp>0)  
         {
            indy=0;
            comp=0;
            printf(lcd_putc,"\f");
            printf(lcd_putc,"error");
            delay_ms(500);
         }
         else
         {
            indy=0;
            indx++;
            printf(lcd_putc,"\f");
            
            ban=0;
         } 
   }//Registro
   exit=0;
   ban=0;
   printf(lcd_putc,"Registrado");
   delay_ms(500);
   printf(lcd_putc,"\f");
  }
  
  
   else if(ban==2)// registro
   {
      int acceso=0;
      indy=0;
      indx=0;
      while(indy<4)
      {
         
         printf(lcd_putc,"\f");
         printf(lcd_putc,"Coloque su dedo");
         lcd_gotoxy(2,2);
      
         while(indy<4)
         {
            if(i2c_poll()) 
            {
               dato=i2c_read();
               if(dato=='*')
                  exit=1;
               else if(dato=='1'||dato=='2'||dato=='3'||dato=='4'||dato=='5'||dato=='6'||dato=='7'||dato=='8'||dato=='9'||dato=='0')
               {
               
                  aux[1][indy]=dato;
                  indy++;
                  lcd_putc(dato);
               }
                              //Muestra dato recibido por pantalla
            }
         }  
   
            for(int k=0;k<5;k++)
            {
               for(int j=0;j<4;j++)
               {
                  if(finger[k][j]==aux[1][j])
                     acceso++;
               }
            
            }
            printf(lcd_putc,"\f");
            if(acceso==4)
            {
               printf(lcd_putc,"Acceso");
               delay_ms(1000);
            }
            else
            {
               printf(lcd_putc,"Acceso denegado");
               delay_ms(1000);
            }
         }
   
      }
  
   }
  
}
  
  
   
   





 
 
 
   

