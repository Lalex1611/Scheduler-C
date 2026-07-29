#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Función que lee desde la posición del puntero hasta el final de la línea.
void read_line(FILE *file)
{
    long pos = ftell(file);
    char ch;

    while((ch = fgetc(file)) != '\n')
        putchar(ch);
    
    printf("\n");

    fseek(file, pos, SEEK_SET);
}

//Función para pasar a la siguiente línea del archivo, independientemente de donde se encuentre el puntero
void goto_next_line(FILE *file)
{
    char ch;
    while((ch = fgetc(file)) != '\n');
}

//Función para ir al inicio de la línea.
void goto_start_line(FILE *file)
{
    int ch;

    for(long pos = ftell(file);(ch = fgetc(file)) != '\n';)
    {
        pos -= 1;
        if(pos < 0)
        {
            fseek(file, 0, SEEK_SET);
            break;
        }
        fseek(file, pos, SEEK_SET);
    }
}

//Función para ir a la línea anterior
void goto_previous_line(FILE *file)
{   
    goto_start_line(file);
    if(ftell(file) <= 0)
        return;
    
    fseek(file, -2, SEEK_CUR);
    goto_start_line(file);
}

int main()
{

    FILE *fp = fopen("./files/8_ISTE_Horarios-2026-2.pdf", "rb");
    char ch;

    if(fp == NULL)
    {
        printf("Unable to open the file\n");
        return 1;
    }

    fseek(fp, 0L, SEEK_END);
    long sz = ftell(fp);
    printf("Size: %ld\n\n", sz);
    sz--;

    fseek(fp, -100, SEEK_END);
    goto_start_line(fp);
    read_line(fp);

    goto_previous_line(fp);
    goto_previous_line(fp);
    read_line(fp);
    
    fclose(fp);

    return 0;
}