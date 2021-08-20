///////////////////////////////////////////////////////////////////////////
////                             KBD_44 V2.C                                ////
////                                //// 
////                 TECLADO 4 X 4                                     ////
////                                                                   ////
////  kbd_init()   Must be called before any other function.           ////
////                                                                   ////
////  c = kbd_getc(c)  Will return a key value if pressed or   0 if not ////
////                   This function should be called frequently so as ////
////                   not to miss a key press.                        ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////


// The following defines the keypad layout on port B

// Funciones para la gestión del teclado de la Trainer PLUS.

// char kbd_getc( )   Devuelve el código ASCII de la tecla pulsada.
//         Si no se pulsó ninguna, devuelve 0.


// Conexiones del teclado.
/*
            RB0 RB1 RB2 RB3
             ^   ^   ^   ^
             |   |   |   |
           |---|---|---|---|
  RB4 ---> | 1 | 2 | 3 | F |
           |---|---|---|---|
  RB5 ---> | 4 | 5 | 6 | E |
           |---|---|---|---|
  RB6 ---> | 7 | 8 | 9 | D |
           |---|---|---|---|
  RB7 ---> | A | 0 | B | C |
           |---|---|---|---|
*/

// Caracteres ASCII asociados a cada tecla:
char const KEYS[4][4] = {{'1','2','3','A'} ,
                         {'4','5','6','B'} ,
                         {'7','8','9','C'} ,
                         {'*','0','#','D'} };

#byte kbd_port_b = 6


char kbd_getc( )
{

//if(input(PIN_B0)) breack;
  char tecla=0;
  int f,c,t,i,j;
  
  port_b_pullups(true);
  set_tris_b(0b00001111); // RB7-RB4 salidas, RB3-RB0 entradas
 
  
  for(f=0x10, i=0; i<4; f<<=1, i++)                  // Termina cuando i=4
  {         
       for(c=0x01, j=0; j<4; c<<=1, j++)        //desplaza c a la isq
                     {
                     kbd_port_b = ~f;         /// escribe
                     delay_cycles(10);                                   //// 1
                     t = kbd_port_b & 0x0F;   /// lee puertob and
                     delay_ms(20);                    // sobretiro prueba20 org
                     t = ~(t | 0xF0 );
                     
                      if(t == c)
                            {  tecla=KEYS[i ][j ];
                              
                               delay_ms(50);                    //20 org
                                          while(t==c)   // lee el teclado
                                          {      //restart_wdt( );
                                             t = kbd_port_b & 0x0F; ///lee puerto
                                             t = ~(t | 0xF0) ;     //0r
                                           }
                                           
                                        break;
                             }
                      }
       
       if(tecla)   break;
  }
  
  port_b_pullups(false);                                    ////
  return tecla;
}


