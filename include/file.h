#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

typedef enum salto {
    WORD = ' ',
    LINE = '\n'
} Salto;

/* FUNCIONES DE LECTURA DE UN ARCHIVO */

/*
*   @brief Función para leer una instancia
*   
*   @param file Archivo a leer
*   @param s Separador a usar
*/
void read(FILE *file, Salto s);

/*
*   @brief Función para obtener una palabra
*
*   @param file Archivo a leer
*
*   @return Palabra leída
*/
char* get_word(FILE *file);

/* FUNCIONES ESTÁNDAR */

/*
*   @brief Función que retorna el tamaño de un archivo
*   
*   @param file Archivo a leer
*/
long get_size(FILE *file);
/*
*   @brief Función para imprimir el tamaño en el formato especificado - Es más como una conversión
*   
*   @param size Tamaño del archivo
*   @param u Unidad a la cual se convertirá el tamaño
*/
void print_size(long size, Unidad u);

/*
*
*
*
*
*/
int compare_word(char *w_one, char *w_two);

/* FUNCIONES DE MOVIMIENTO DE UN ARCHIVO */

/*
*   @brief Función para pasar a la siguiente instancia
*   
*   @param file Archivo a leer
*   @param s Separador a usar
*/
void goto_next(FILE *file, Salto s);
/*
*   @brief Función para ir a la instancia anterior
*   
*   @param file Archivo a leer
*   @param s Separador a usar
*/
void goto_previous(FILE *file, Salto s);
/*
*   @brief Función para ir al inicio de la instancia
*   
*   @param file Archivo a leer
*   @param s Separador a usar
*/
void goto_start(FILE *file, Salto s);
/*
*   @brief Función para ir n líneas adelante o atras
*   
*   @param file Archivo a leer
*   @param s Separador a usar
*/
void goto_n(FILE *file, int n, Direction d, Salto s);