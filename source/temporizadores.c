/*-------------------------------------
 temporizadores.c
-------------------------------------*/
// Anadir los includes que sean necesarios
#include "defines.h"
#include "sprites.h"
#include <nds.h>
#include <stdio.h>
#include "estados.h"
#include "utilidades.h"

int tic = 0;
int sec = 0;


int temp_billete=0;
// Rutina de atencion a la interrupcion del temporizador
void IntTemp() {

    switch(estado){
        case E_JUGANDO:
            tic++;
            if(tic >= 512){//256
                tic = 0;
                sec--;
                printf("\x1b[08;09H %d ",sec);
                temp_billete++;
                if(sec <= 0){
                    finalizar_partida();
                }
            }
            if (temp_billete >= 1){
                //crear_billete = 1;
                flags |= 0x4;//Crear billete
                temp_billete = 0;
            }
            if (tic % velocidad_billete == 0){
                flags |= 0x2;//caer billete
            }
            timer_partida--;
            if(timer_partida == 0){
                finalizar_partida();
            }
            break;
        case E_START:
        case E_STANDBY:
        case E_FIN:
        default:
            break;
    }
}





