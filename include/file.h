#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum direction {
    GOTO_NEXT,
    GOTO_PREVIOUS
} Direction;

/*
*   FUNCIONES ESPECÍFICAS DE MOVIMIENTO Y LECTURA DE UN ARCHIVO
*/

// Función que lee desde la posición del puntero hasta el final de la línea.
void read_line(FILE *file);
// Función para pasar a la siguiente línea del archivo, independientemente de donde se encuentre el puntero
void goto_next_line(FILE *file);
// Función para ir a la línea anterior
void goto_previous_line(FILE *file);
// Función para ir al inicio de la línea.
void goto_start_line(FILE *file);

// Función para ir n líneas adelante o atras
void goto_n_lines(FILE *file, int n, Direction d);