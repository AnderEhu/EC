#include <nds.h>
#include <stdio.h>
#include "defines.h"

int chapuza = 0;
void  e_jugando(){
    switch(tecla){
        case DCHA:
        if (chapuza >=3){
            pos_sobre++;
            if(pos_sobre >= 256) pos_sobre = 0;
            chapuza = 0;
        } else {
            chapuza++;
        }
        break;
        default:
                   break;
    }
    MostrarSobre(pos_sobre, POS_Y_SOBRE);
}
