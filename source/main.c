/*---------------------------------------------------
  Este codigo se ha implementado basandose en el ejemplo "Simple sprite demo" de
  dovoto y otro de Jaeden Amero
  ---------------------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>	    // srand, rand,...
#include <unistd.h>
#include <time.h>       // time

#include "fondos.h"
#include "sprites.h"
#include "defines.h"
#include "rutservs.h"
#include "teclado.h"
#include "temporizadores.h"
#include "estados.h"
#include "utilidades.h"

//---------------------------------------------------
// Funciones
//---------------------------------------------------

// Esta funcion consulta si se ha tocado la pantalla tactil
int TactilTocada() {
    touchPosition pos_pantalla;
    touchRead(&pos_pantalla);
    return !(pos_pantalla.px==0 && pos_pantalla.py==0);
}

//---------------------------------------------------
// Variables globales
//---------------------------------------------------
//billete[*][0] = indice
//billete[*][1] = x
//billete[*][2] = y
//billete[*][3] = tipo [0=normal, 1= sucio]
int billetes [10][4] = {
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1}
};
int estado = E_START;
int tecla = -1;
// 5 = normal | 7 = facil | 3 = dificil
int velocidad_billete = 5;


// +--------------------+
//4| sobre o maletin    |
//3| refrescar pantalla |
//2| crear billete      |
//1| caer billete       |
//0| actualizar sobre   |
// +--------------------+
int flags = 0;
//---------------------------------------------------
// main
//---------------------------------------------------
int pos_sobre= 128;
int billetes_cogidos = 0;
int billetes_perdidos = 0;
int timer_partida = 0;

int dificultad;

int main() {
    /* Definir variables */
    touchPosition pos_pantalla;
    int chapuza = 0;

    /* Poner en marcha el motor grafico 2D. */
    powerOn(POWER_ALL_2D);

    /* Establecer la pantalla inferior como principal, inicializar el sistema grafico
       y configurar el sistema de fondos. */
    lcdMainOnBottom();
    initVideo();
    initFondos();

    /* Mostrar fondos en pantalla. */
    SetFondo();
    //mostrarFondoSub();

    /* Inicializar memoria de sprites y guardar en ella los sprites */
    initSpriteMem();
    guardarSpritesEnMemoria();

    /* Establecer las paletas para los sprites */
    establecerPaletaPrincipal();
    establecerPaletaSecundaria();

    /* Inicializa la consola (superior) de texto.
       Nota.- Para borrar la pantalla existe la funcion consoleClear() */
    consoleDemoInit();

    /* Para inicializar el generador de numeros aleatorios en funcion de una semilla,
       en este caso time(NULL). srand() solo se suele activar una vez por ejecucion y
       no devuelve ningun valor.
       La funcion para generar valores aleatorios en el resto del programa es rand() */
    srand (time(NULL));

    interrupciones();
    /* Incluimos la siguiente cabecera para que cada grupo la modifique con
       su numero de grupo "xx" en "Gxx". */
    printf("\x1b[02;00H  +--------------------------+  ");
    printf("\x1b[03;00H  : EC 17/18           G26   :  ");
    printf("\x1b[04;00H  +--------------------------+  ");
    pantalla_de_inicio();
    //---------------------------------------------------
    //
    dificultad = FACIL;
    while(estado != E_FIN) {
        tecla = TeclaPulsada();
        actualizar_panel_enq();

        switch(estado){
            case E_JUGANDO:
                if(tecla == DCHA){
                    if (chapuza >= 1200){
                        chapuza = 0;
                        pos_sobre++;
                        if(pos_sobre >= 256) pos_sobre = 0;
                        flags |= F_AC_SOBRE;
                    } else {
                        chapuza++;
                    }
                }
                break;
            case E_START:
                if(TactilTocada()){
                    iniciar_partida();
                }else if(tecla == ARRIBA){
                    if(chapuza >= 40000){
                        chapuza = 0;
                        dificultad--;
                        if(dificultad <= 0) dificultad = 3;

                        flags |= F_REF_PANTALLA;//refrescar pantalla;
                    }
                }else if(tecla == ABAJO){
                    if(chapuza >= 40000){
                        chapuza=0;
                        dificultad++;
                        if(dificultad >= 4) dificultad = 1;
                        flags |= F_REF_PANTALLA;//refrescar pantalla
                    }
                }
                chapuza++;
                break;
            case E_STANDBY:
                if(tecla == START){
                    iniciar_partida();
                }
            case E_FIN:
            default:
                break;
        }

        actualizar_flags();
    } // while

} //main

void actualizar_billete(i){
    MostrarBillete(billetes[i]);
}


void actualizar_flags(){
    switch(estado){
        case E_START:
            if(flags & F_REF_PANTALLA){//refrescar pantalla
                printf("\x1b[%d;05H>",10+((dificultad+2)%3));
                printf("\x1b[%d;05H ",10+(dificultad)%3);
                printf("\x1b[%d;05H ",10+(dificultad+1)%3);
                flags &= ~F_REF_PANTALLA;
            }
            break;
        case E_JUGANDO:
            if(flags & F_AC_SOBRE){//Actualizar sobre
                mostrar_sobre();
                flags &= ~F_AC_SOBRE;
            }
            if (flags & F_CREAR_BILLETE){//crear billete
                for(int i = 0; i<10;i++){
                    if (billetes[i][0] == -1){
                        billetes[i][0]=i;
                        billetes[i][1]=rand()%240;//256-16
                        billetes[i][2] = 12;
                        billetes[i][3] = ((rand()%10) ==1);
                        actualizar_billete(i);
                        break;
                    }
                }
                flags &= ~F_CREAR_BILLETE;
            }
            if (flags & F_CAER_BILLETE){// caer billete
                for(int i = 0; i<10; i++){
                    if (billetes[i][0]!=-1){
                        billetes[i][2] += 1;
                        if (billetes[i][2]+6>POS_Y_SOBRE){
                            //Posible colision con y
                            if ( billetes[i][1]+16>pos_sobre && billetes[i][1]<pos_sobre+16){
                                //Colision con sobre
                                //y billete recogido
                                if(billetes[i][3] == 0){
                                    BorrarBillete(billetes[i]);
                                    billetes[i][0] = -1;
                                    billetes[i][1] = -1;
                                    billetes[i][2] = -1;

                                    billetes_cogidos++;
                                    actualizar_puntiacion();
                                    if(billetes_cogidos == 20){
                                        flags |= F_SOBRE;//sobre o maletin
                                        flags |= F_AC_SOBRE;//actualizar sobre
                                    }
                                }else{
                                    finalizar_partida();
                                }
                            }else if(billetes[i][2] >= 191){
                                //Billete perdido
                                BorrarBillete(billetes[i]);
                                billetes[i][0] = -1;
                                billetes[i][1] = -1;
                                billetes[i][2] = -1;
                                billetes_perdidos++;
                                actualizar_puntiacion();
                            }

                        }
                        actualizar_billete(i);
                    }
                }
                flags &= ~F_CAER_BILLETE;
            }
            break;
        case E_STANDBY:
        case E_FIN:
        default:
            break;
    }


}
//switch(estado){
//    case E_START:
//    case E_JUGANDO:
//    case E_STANDBY:
//    case E_FIN:
//    default:
//        break;
//}
//
void limpiar_pantalla(){
    for(int i = 5; i<=16; i++){
        printf("\x1b[%d;00H                                ",i);
    }
}

void iniciar_partida(){
    billetes_perdidos = 0;
    billetes_cogidos = 0;
    sec=60;
    flags = 0;
    limpiar_pantalla();
    mostrar_panel_puntos();
    actualizar_puntiacion();
    printf("\x1b[08;09H %d ",sec);
    pos_sobre = 128;
    mostrar_sobre();
    estado = E_JUGANDO;

    switch(dificultad){
        case FACIL:
            velocidad_billete = 7;
            break;
        case NORMAL:
            velocidad_billete = 5;
            break;
        case DIFICIL:
            velocidad_billete = 3;
            break;
        default: break;
    }
}


void mostrar_panel_puntos(){
    printf("\x1b[08;00H Tiempo:     segundos restantes");
    printf("\x1b[09;00H Billetes recogidos:");
    printf("\x1b[10;00H Billetes perdidos:");
}

void actualizar_puntiacion(){

    printf("\x1b[09;20H %d",billetes_cogidos);
    printf("\x1b[10;20H %d",billetes_perdidos);
}


void finalizar_partida(){
    for(int i = 0;i<10; i++){
        BorrarBillete(billetes[i]);
        billetes[i][0] = -1;
        billetes[i][1] = -1;
        billetes[i][2] = -1;
    }
    BorrarSobre(pos_sobre,POS_Y_SOBRE);
    printf("\x1b[08;09H %d ",sec);

    printf("\x1b[12;00H Pulsa <START> para reintentar");
    printf("\x1b[13;00H Pulsa <SELECT> para reiniciar");

    estado = E_STANDBY;

}


void pantalla_de_inicio(){
    estado = E_START;
    limpiar_pantalla();
    printf("\x1b[07;04H  Para comenzar, toque");
    printf("\x1b[08;05H  la pantalla tactil");
    printf("\x1b[10;05H  FACIL");
    printf("\x1b[11;05H  NORMAL");
    printf("\x1b[12;05H  DIFICIL");
    flags |= F_REF_PANTALLA; //refrescar pantalla
}
