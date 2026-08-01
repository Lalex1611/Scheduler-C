#include "../include/pdf_parser.h"

int find_trailerX(FILE *file, int limit)
{
    fseek(file, -1, SEEK_END);

    int seguir = 1; 
    char *palabra;

    while(seguir > 0)
    {
        goto_previous(file, LINE);
        palabra = get_word(file);
        if(compare_word(palabra, "trailer"))
        {
            free(palabra);
            return 0;
        }

        seguir++;
        if(seguir > limit)
        {
            free(palabra);
            return 1;
        }
    }
    
    free(palabra);
    return 1;
}
