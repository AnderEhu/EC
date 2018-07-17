
#include <nds.h>
#include <stdio.h>
#include <stdlib.h>	    // srand, rand,...
#include <unistd.h>
#include <time.h>       // time

#include "fondos.h"
#include "sprites.h"
#include "defines.h"

void mover_izda(){
    pos_sobre -= 5;
    if(pos_sobre <= -16) pos_sobre = 255;
}


void mostrar_sobre(){
    MostrarSobre(pos_sobre,POS_Y_SOBRE);
}

void actualizar_panel_int(int tecla){
  //  printf("\x1b[09;06H        ");
  //  switch(tecla){
  //      case B:      printf("\x1b[09;08H B "); break;
  //      case SELECT: printf("\x1b[09;06H SELECT "); break;
  //      case IZDA:   printf("\x1b[09;06H IZDA "); break;
  //  }
  //  iprintf("\x1b[09;16H:%3d  : %04X :  ",tecla, TECLAS_DAT);
}

void actualizar_panel_enq(){
    //if(tecla != START && tecla != A && tecla != DCHA){
    //    return;
    //}
    //    printf("\x1b[06;06H        ");
    //    //Borrar espacio de tecla
    //    switch(tecla){
    //        case A:      printf("\x1b[06;08H A ");      break;
    //        case R:      printf("\x1b[06;08H R ");      break;
    //        case L:      printf("\x1b[06;08H L");       break;
    //        case START:  printf("\x1b[06;06H START ");  break;
    //        case DCHA:   printf("\x1b[06;06H DCHA ");   break;
    //        case ARRIBA: printf("\x1b[06;06H ARRIBA "); break;
    //        case ABAJO:  printf("\x1b[06;06H ABAJO ");  break;
    //    }
    //    iprintf("\x1b[06;16H:%3d  : %04X :  ",tecla, TECLAS_DAT);
}
