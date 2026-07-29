#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef enum direction {
    GOTO_NEXT,
    GOTO_PREVIOUS
} Direction;

typedef enum unidad {
    B,
    KB,
    MB,
    GB
} Unidad;

/*
*   FUNCIONES DE LECTURA DE UN ARCHIVO
*/

// Función que lee desde la posición del puntero hasta el final de la línea.
void read_line(FILE *file);
// Función que retorna el tamaño (en bytes) de un archivo
long get_size(FILE *file);
// Función para imprimir el tamaño en el formato especificado
void print_size(long size, Unidad u);

/*
*   FUNCIONES DE MOVIMIENTO DE UN ARCHIVO
*/

// Función para pasar a la siguiente línea del archivo, independientemente de donde se encuentre el puntero
void goto_next_line(FILE *file);
// Función para ir a la línea anterior
void goto_previous_line(FILE *file);
// Función para ir al inicio de la línea.
void goto_start_line(FILE *file);

// Función para ir n líneas adelante o atras
void goto_n_lines(FILE *file, int n, Direction d);