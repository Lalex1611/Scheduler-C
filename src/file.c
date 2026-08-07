#include "../include/file.h"

 const char Saltos[]=
{
    ' ',
    '\n',
    '/'
};

void read(FILE *file, Salto s)
{
    long pos = ftell(file);
    char ch;
    char salto = get_salto(s);

    while((ch = fgetc(file)) != salto)
        putchar(ch);
    
    printf("\n");

    fseek(file, pos, SEEK_SET);
}

char* get_word(FILE *file, Position pos)
{
    long og_pos = ftell(file);
    // Ir al inicio de la palabra
    if(pos == SET_START) goto_start(file, WORD);

    char palabra[100];
    char ch;
    int i = 0;
    
    // Obtener la palabra y su tamaño
    ch = fgetc(file);
    while(!in_saltos(ch) && ch != EOF && i < 99)
    {
        palabra[i] = ch;
        i++;
        ch = fgetc(file);
    }
    
    palabra[i] = '\0';
    
    char* return_palabra = (char*)calloc(i + 1, sizeof(char));

    strcpy(return_palabra, palabra);
    
    fseek(file, og_pos, SEEK_SET);
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

char get_salto(Salto s)
{
    return Saltos[s];
}

int in_saltos(char s)
{
    for(int i = 0; i < _COUNT; i++)
    {
        if(s == Saltos[i]) return 1;
    }

    return 0;
}

int compare_word(char *w_one, char *w_two)
{
    if(strlen(w_one) != strlen(w_two)) return 0;

    for(int i = 0; w_one[i] != '\0' && w_two[i] != '\0'; i++)
    {
        if(w_one[i] != w_two[i])
            return 0;
    }

    return 1;
}

void goto_next(FILE *file, Salto s)
{
    char ch, salto = get_salto(s);
    while((ch = fgetc(file)) != salto);
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
    char salto = get_salto(s);

    for(long pos = ftell(file);(ch = fgetc(file)) != salto;)
    {
        if(ch == Saltos[LINE])
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