#include "../include/pdf_parser.h"

int find_targetX(FindTargetOpts opts)
{
    char target[10];
    switch(opts.type)
    {
        case PDF_XREF:
            strcpy(target,"xref");
            break;
        case PDF_STARTXREF:
            strcpy(target,"startxref");
            break;
        default:
            strcpy(target, "trailer");
            break;
    }

    fseek(opts.file, -1, SEEK_END);

    int seguir = 1; 
    char *palabra;

    while(seguir > 0)
    {
        goto_previous(opts.file, LINE);
        palabra = get_word(opts.file, SET_START);
        if(compare_word(palabra, target))
        {
            free(palabra);
            return 0;
        }

        seguir++;
        if(seguir > opts.limit)
        {
            free(palabra);
            return 1;
        }
    }
    
    free(palabra);
    return 1;
}

//TODO: Agregar un macro de error para no retornar un simple 1 en caso de error

long int get_xref(FILE* file)
{
    if(find_target(.file = file, .type = PDF_STARTXREF))
        return 1;
    
    goto_next(file, LINE);
    char *ref_s = get_word(file, SET_START);
    long int ref_i = strtol(ref_s, NULL, 10);

    free(ref_s);
    return ref_i;
}

int get_root(FILE* file)
{
    /* Por default ya se busca el PDF_TRAILER */
    if(find_target(.file = file))
        return 1;
        
    /* Se pasa a la siguiente línea ya que ahí empieza la información */
    goto_next(file, LINE);
    /* Ir al siguiente NAME para empezar a comparar */
    goto_next(file, NAME);

    /* Se especifica que empiece desde donde esta y no del inicio de lo que considera palabra */
    /* Sin NOT_START -> Palabra retornada: "[contenido_basura]/Root" */
    /* Con NOT_START -> Palabra retornada: "Root" */
    char *name = get_word(file, NOT_START);
    
    while(!compare_word(name, "Root"))
    {
        goto_next(file, NAME);
        name = get_word(file, NOT_START);
    }

    goto_next(file, WORD);
    name = get_word(file, SET_START);
    int object_num = strtol(name, NULL, 10);
    free(name);

    return object_num;
}