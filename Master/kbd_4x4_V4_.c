///////////////////////////////////////////////////////////////////////////
////                             keypad.c                                          ////
////                  Driver para teclado 4x4 generico                   ////
////                                                                                    ////
////  init_keypad()   Debe llamarse desde el programa principal ////
////                  antes de cualquier funcion                             ////
////                        ////
////  scan_keypad()   Función de escaneo de teclado segun    ////
////      la matriz de teclado                ////
////                                                                                    ////
////  read_keypad()     Encuentra la tecla por el metodo de inversion   ////
////        de puerto, espera a que se deje de pulsar y  //// 
////              retorna.       ////
////                                                                           ////
///////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,2009 Custom Computer Services           ////
//// This source code may only be used by licensed users of the CCS C  ////
//// compiler.  This source code may only be distributed to other      ////
//// licensed users of the CCS C compiler.  No other use, reproduction ////
//// or distribution is permitted without written permission.          ////
//// Derivative programs created using this software in object code    ////
//// form are not restricted in any way.                               ////
///////////////////////////////////////////////////////////////////////////
////                                           
////   RB4 RB5 RB6 RB7                               
////             ^   ^   ^   ^                                 
////             |   |   |   |                                 
////           |---|---|---|---|      El teclado se conecta sin      
////  RB0 ---> | 1 | 2 | 3 | A |      necesedad de resistencias ya  
////           |---|---|---|---|      que tiene las resistencias de  
////  RB1 ---> | 4 | 5 | 6 | B |      pull-up activadas             
////           |---|---|---|---|                           
////  RB1 ---> | 7 | 8 | 9 | C |                              
////           |---|---|---|---|                              
////  RB3 ---> | * | 0 | # | D |                              
////           |---|---|---|---|                              
////                                           
///////////////////////////////////////////////////////////////////////////
 
 
 
//Direcciones de los registros segun PDF del pic 16fXXX
 
#byte PORTB=0x06   //Pic 16f877a
#byte TRISB=0x86   //
#byte INTCON=0x0B

void init_keypad()   
{

   TRISB=0xF0;
   port_b_pullups (TRUE);    //Habilita pull-up internos del puerto B   
   PORTB=0xF0;
   enable_interrupts(INT_RB);      // Habilita la interrupcion del puerto B ( RB4 - RB7).
   enable_interrupts(GLOBAL);      // Habilita las interrupciones globales.
}
 
unsigned char scan_keypad()   
{
   unsigned char i=0,j=0,PORT,PORTH,PORTL,PH,PL,key;
 
   //Matriz de teclado
   char keypad[4][4] =   { {'1','2','3','A'},
                       {'4','5','6','B'},
                      {'7','8','9','C'},
                      {'E','0','F','D'} }; 
   PORT=PORTB;
   PORTH=PORT&0xF0;
   PORTL=PORT&0x0F;
   
   for(j=0;j<4;j++)
   {
      PH=~(0b00010000<<j)&0xF0;
      if(PORTH == PH)
      {
         for(i=0;i<4;i++)
         {
            PL=~(0b00000001<<i)&0x0F;
            if(PORTL == PL)
            {
               key=keypad[i][j];
               while(PORT==PORTB);
            }
         }
      }      
   }
   if(key)
      return(key);   //Si la tecla es encontrada retorna valor segun la matriz de teclado
   else   
      return(0x80);   //Si la tecla no es encontrada retorna un caracter nulo 
}
 
 
unsigned char read_keypad()
{   
   char read,key;
 
   read=PORTB;
   TRISB=0x0F;
   PORTB=read;
   key=scan_keypad();
   return(key);
}