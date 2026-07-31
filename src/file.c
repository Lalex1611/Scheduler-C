#include "../include/file.h"

void read(FILE *file, Salto s)
{
    long pos = ftell(file);
    char ch;

    while((ch = fgetc(file)) != (char)s)
        putchar(ch);
    
    printf("\n");

    fseek(file, pos, SEEK_SET);
}

char* get_word(FILE *file)
{
    // Ir al inicio de la palabra
    goto_start(file, WORD);

    char palabra[100];
    char ch;
    int i = 0;
    
    // Obtener la palabra y su tamaño
    for(;(ch = fgetc(file)) != (char)WORD;i++)
        palabra[i] = ch;
    
    palabra[i] = '\0';
    
    char* return_palabra = (char*)calloc(i, sizeof(char));

    strcpy(return_palabra, palabra);
    
    return return_palabra;
}

long get_size(FILE *file)
{
    long sz, og_pos;

    og_pos = ftell(file);
    fseek(file, 0L, SEEK_END);
    sz = ftell(file);

    fseek(file, og_pos, SEEK_SET);

    return sz;
}

void print_size(long size, Unidad u)
{
    char ch[] = "\0KMG"; 

    printf("Tamaño: %.2f%cB\n", (size / pow(1024,u)), ch[u]);
}

void goto_next(FILE *file, Salto s)
{
    char ch;
    while((ch = fgetc(file)) != (char)s);
}

void goto_previous(FILE *file, Salto s)
{
    goto_start(file, s);
    if(ftell(file) <= 0)
        return;
    
    fseek(file, -2, SEEK_CUR);
    goto_start(file, s);
}

void goto_start(FILE *file, Salto s)
{
    int ch;

    for(long pos = ftell(file);(ch = fgetc(file)) != (char)s;)
    {
        if(ch == (char)LINE)
            break;

        pos -= 1;
        if(pos < 0)
        {
            fseek(file, 0, SEEK_SET);
            break;
        }
        fseek(file, pos, SEEK_SET);
    }
}

void goto_n(FILE *file, int n, Direction d, Salto s)
{
    switch(d)
    {
        case GOTO_NEXT:
            for(int i = 0; i < n; i++)
                goto_next(file, s);
            break;
        case GOTO_PREVIOUS:
            for(int i = 0; i < n; i++)
                goto_previous(file, s);
            break;
        default:
            printf("Dirección NO especificada\n");
            break;
    }
}