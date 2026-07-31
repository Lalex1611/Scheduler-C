#include "../include/file.h"

int main()
{

    FILE *fp = fopen("./files/8_ISTE_Horarios-2026-2.pdf", "rb");

    if(fp == NULL)
    {
        printf("Unable to open the file\n");
        return 1;
    }

    print_size(get_size(fp), KB),

    fseek(fp, -100, SEEK_END);
    goto_start(fp, WORD);
    read(fp, WORD);
    goto_start(fp, LINE);
    read(fp, LINE);

    goto_n(fp, 2, GOTO_PREVIOUS, LINE);
    read(fp, LINE);
    read(fp, WORD);
    goto_next(fp, WORD);
    read(fp, WORD);
    goto_previous(fp, WORD);
    read(fp, WORD);

    char* palabra = get_word(fp);

    printf("Palabra: %s\n",palabra);
    
    fclose(fp);

    free(palabra);

    return 0;
}