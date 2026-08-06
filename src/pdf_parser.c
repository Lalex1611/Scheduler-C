#include "../include/pdf_parser.h"

const char *Objetos[] = 
{
    "Root",
    "Info",
    "Pages",
    "Page",
    "Count"
};


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
            return ERROR;
        }
    }
    
    free(palabra);
    return ERROR;
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

void goto_obj(FILE* file, PdfObject obj)
{
    /* Se especifica que empiece desde donde esta y no del inicio de lo que considera palabra */
    /* Sin NOT_START -> Palabra retornada: "[contenido_basura]/Root" */
    /* Con NOT_START -> Palabra retornada: "Root" */
    char *name = get_word(file, NOT_START);
    
    while(!compare_word(name, (char*)Objetos[obj]))
    {
        goto_next(file, NAME);
        name = get_word(file, NOT_START);
    }
    
    free(name);
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

    goto_obj(file, ROOT);

    goto_next(file, WORD);
    char *name = get_word(file, SET_START);
    int object_num = strtol(name, NULL, 10);
    free(name);

    return object_num;
}

long get_obj_offset(FILE *file, int obj)
{
    long int xref_table = get_xref(file);
    fseek(file, xref_table, SEEK_SET);

    goto_next(file, LINE);
    goto_n(file, obj + 1, GOTO_NEXT, LINE);

    char *offset_s = get_word(file, SET_START);
    long int offset_l = strtol(offset_s, NULL, 10);
    
    free(offset_s);
    return offset_l;
}

int get_pages_count(FILE *file)
{
    int root_ref = get_root(file);
    long int root_offset = get_obj_offset(file, root_ref);
    fseek(file, root_offset, SEEK_SET);

    goto_obj(file, PAGES);

    goto_next(file, WORD);

    char *pages_ref = get_word(file, SET_START);
    int pages_obj = strtol(pages_ref, NULL, 10);
    free(pages_ref);

    long int pages_offset = get_obj_offset(file, pages_obj);
    fseek(file, pages_offset, SEEK_SET);
    goto_next(file, LINE);

    goto_obj(file, COUNT);
    goto_next(file, WORD);
    char *pages_count = get_word(file, SET_START);
    printf("Número de páginas: %s\n", pages_count);

    return 0;
}