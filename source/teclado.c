/*-------------------------------------
 teclado.c
-------------------------------------*/

// Anadir los includes que sean necesarios
#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "sprites.h"

// Esta funcion tiene que devolver el valor de la tecla pulsada
int  TeclaPulsada() {
   // Devuelve el valor asociado a la tecla pulsada:
   // A=0; B=1; Select=2; Start=3; Der=4; Izq=5;
   // Arriba=6; Abajo=7; R=8; L=9;
   // -1 en otros casos
    if((TECLAS_DAT & 0x1) == 0){
        return A;
    }else if((TECLAS_DAT &  0x2) == 0){
        return B;
    }else if((TECLAS_DAT & 0x4) == 0){
        return SELECT;
    }else if((TECLAS_DAT & 0x8) == 0){
        return START;
    }else if((TECLAS_DAT & 0x10) == 0){
        return DCHA;
    }else if((TECLAS_DAT & 0x20) == 0){
        return IZDA;
    }else if((TECLAS_DAT & 0x40) == 0){
        return ARRIBA;
    }else if((TECLAS_DAT & 0x80) == 0){
        return ABAJO;
    }else if((TECLAS_DAT & 0x100) == 0){
        return R;
    }else if((TECLAS_DAT & 0x200) == 0){
        return L;
    }else {
        return -1;
    }
}


// Rutina de atencion a la interrupcion del teclado
void IntTec() {

    int tecla = TeclaPulsada();
    //actualizar_panel_int(tecla);
    switch(estado){
        case E_START: break;
        case E_JUGANDO:
            if (tecla == IZDA){
                mover_izda();
                flags |= F_AC_SOBRE;
            }
            if(tecla == B){
                finalizar_partida();
            }
            break;
        case E_STANDBY:
            if(tecla == SELECT){
                pantalla_de_inicio();
            }
            break;
        case E_FIN:
        default:
            break;
    }
}


