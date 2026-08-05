#include "file.h"

typedef enum
{
    PDF_TRAILER,
    PDF_STARTXREF,
    PDF_XREF
} PdfPart;

typedef struct
{
    FILE *file;
    int limit;
    PdfPart type;
} FindTargetOpts;

/*
*   Función que nos deja en una posición deseada
*
*   @param FindTargetOpts Struct que incluye referencia al archivo (obligatorio), un limite y el tipo de target a buscar
*
*   @return 
*   0 -> Si la busqueda fue exitosa
*/
int find_targetX(FindTargetOpts opts);

#define find_target(...) \
    find_targetX((FindTargetOpts){.limit = 100, .type = PDF_TRAILER, __VA_ARGS__})

/*
*   Función que obtiene el offset de la tabla xref
*
*   @param file Archivo a leer
*
*   @return bytes del offset
*/
long int get_xref(FILE* file);

/*
*   Función que obtiene el número de objeto del root
*
*   @param file Archivo a leer
*
*   @return Número de objeto del root
*/
int get_root(FILE* file);

/*
*   @brief Función que retorna el offset de un objeto
*
*   @param file Archivo a explorar
*   @param obj Número de objeto a buscar
*
*   @return Offset del objeto
*/
long get_obj_offset(FILE *file, int obj);