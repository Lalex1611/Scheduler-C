#include "../include/pdf_parser.h"

int find_trailerX(FindTrailerOpts opts)
{
    fseek(opts.file, -1, SEEK_END);

    int seguir = 1; 
    char *palabra;

    while(seguir > 0)
    {
        goto_previous(opts.file, LINE);
        palabra = get_word(opts.file);
        if(compare_word(palabra, "trailer"))
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
