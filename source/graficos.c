/*---------------------------------------------------------------------------------
Este codigo se ha implementado basandose en el ejemplo "Simple sprite demo" de 
dovoto y otro de Jaeden Amero
---------------------------------------------------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Definir el sistema de video */
void initVideo() {
    /*  Mapear la memoria VRAM para mostrar graficos en las dos pantallas. */

    vramSetMainBanks(VRAM_A_MAIN_BG_0x06000000,
                     VRAM_B_MAIN_BG_0x06020000,
                     VRAM_C_SUB_BG_0x06200000,
                     VRAM_E_LCD);

    vramSetBankE(VRAM_E_MAIN_SPRITE);
    vramSetBankD(VRAM_D_SUB_SPRITE);

    /*  Establecer el modo de video de la pantalla principal. */
    videoSetMode(MODE_5_2D | // Establecer el modo grafico 5
                 DISPLAY_BG2_ACTIVE | // Activar el fondo 2
                 DISPLAY_BG3_ACTIVE); // Activar el fondo 3

    /*  Establecer el modo de video de la pantalla secundaria. */
    videoSetModeSub(MODE_5_2D | // Establecer el modo grafico 5
                    DISPLAY_BG3_ACTIVE); // Activar el fondo 3
}



