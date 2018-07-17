extern u16* gfxBillete;
extern u16* gfxSobre;

/* Inicializar la memoria de Sprites. */
extern void initSpriteMem();

/* Dentro de esta funcion hay que definir el color con el que se mostrara cada uno de los 256
 * colores posibles en la pantalla principal. El 0 es transparente y los no definidos son negros.
 */
extern void establecerPaletaPrincipal();

/* Dentro de esta funcion hay que definir el color con el que se mostrara cada uno de los 256
 * colores posibles en la pantalla secundaria. El 0 es transparente y los no definidos son negros.
 */
extern void establecerPaletaSecundaria();

/* Para guardar los sprites en memoria y luego poder usarlos. */

extern void guardarSpritesEnMemoria();

/* Funciones especificas para manejar los sprites. */

extern void MostrarBillete(int billete[]);
extern void BorrarBillete(int billete[]);

extern void MostrarSobre(int x, int y);
extern void BorrarSobre(int x, int y);


