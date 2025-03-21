#ifndef __UTIL_H_ 
// Esta línea es una *guarda de preprocesador*. 
// Sirve para evitar que este archivo sea incluido más de una vez durante la compilación.
// Si __UTIL_H_ no está definido, se define en la siguiente línea:

#define __UTIL_H_


// Incluimos la librería Arduino.h para acceder a funciones y definiciones estándar de Arduino.
#include <Arduino.h>


#ifdef __cplusplus
// Este bloque es importante cuando trabajamos con C++.
// Si el código que incluye este archivo se compila como C++,
// `extern "C"` asegura que las funciones declaradas aquí se traten como C puro.
// Esto evita errores de enlace en proyectos que mezclan C y C++.
extern "C" 
{
#endif

// Declaración de las funciones que estarán disponibles en la biblioteca:
// te juro que lo intenté pero no estarioa funcionando

// =====================================================================
// *** Prototipos de funciones declarados aquí ***
// =====================================================================

void setup_timer0(void); // Configura el Timer 0 del microcontrolador.
void config_io(void);    // Configura los pines de entrada/salida (I/O).


#ifdef __cplusplus
} 
// Aquí termina el bloque `extern "C"`.
// Esto se asegura de cerrar correctamente el código que podría estar siendo compilado como C++.
#endif

#endif //__UTIL_H_ 
// Esta línea cierra la guarda de preprocesador iniciada al principio (#ifndef).
// Si este archivo se incluye más de una vez, las guardas evitan que se procese de nuevo
// (porque __UTIL_H_ ya estaría definido después de la primera inclusión).
