// Este procedimiento inicializa la tabla de interrupciones para que el gestor de interrupciones sepa
// que rutina de atencion tiene que ejecutar cuando le llega una peticion de interrupcion. Ademas es 
// aqui donde se configuran los registros de control de los perifericos.

extern void interrupciones();

extern void HabilitarInterrupciones();
extern void ProgramarRegistrosControl();
extern void DefinirVectorInterrupciones();
extern void InhibirInterrupciones();
