#include "../include/file.h"

int main()
{

    FILE *fp = fopen("./files/8_ISTE_Horarios-2026-2.pdf", "rb");

    if(fp == NULL)
    {
        printf("Unable to open the file\n");
        return 1;
    }

    print_size(get_size(fp), KB);
    fseek(fp, -1, SEEK_END);

    int seguir = 1;

    char *palabra;

    //FIXME: Pasar esto a una función especifica de encontrar palabra
    while(seguir > 0)
    {
        goto_previous(fp, LINE);
        palabra = get_word(fp);
        if(compare_word(palabra, "trailer"))
        {
            printf("yahoo\n");
            break;
        }
        seguir++;
        if(seguir > 100)
            break;
    }
    
    free(palabra);
    fclose(fp);

    return 0;
}