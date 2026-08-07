#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define ERROR -1

typedef enum direction {
    GOTO_NEXT,
    GOTO_PREVIOUS
} Direction;

typedef enum {
    SET_START,
    NOT_START,
    SET_END,
    NOT_END
} Position;

typedef enum unidad {
    B,
    KB,
    MB,
    GB
} Unidad;

typedef enum salto {
    WORD,
    LINE,
    NAME,
    _COUNT
} Salto;

extern const char Saltos[_COUNT];

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
*   @param pos Posicion desde donde emepezar
*
*   @return Palabra leída
*/
char* get_word(FILE *file, Position pos);

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
*   @brief Función que retorna el char equivalente al salto del enum 
*
*   @param s Salto seleccionado
*
*   @return Caracter equivalente
**/
char get_salto(Salto s);

/*
*   @brief Función que confirma si el carácter es uno de los diferentes tipos de salto
*
*   @param s Carácter a comparar
*
*   @return 
*   1 -> El char es un salto
*   0 -> El char no es un salto
*/
int in_saltos(char s);

/*
*   @brief Función para comparar dos palabras
*
*   @param w_one Primer palabra a comparar
*   @param w_two Sgunda palabra a comparar
*
*   @return 1 si la palabra es igual - 0 si es diferente
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