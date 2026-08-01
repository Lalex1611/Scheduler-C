#include "file.h"
#include "vrg.h"

#define find_trailer(...) find_trailerX(__VA_ARGS__, 100)

/* FUNCIONES PARA ENCONTRAR PARTES DEL PDF */
int find_trailerX(FILE *file, int limit);