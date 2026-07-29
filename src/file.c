#include "../include/file.h"

void read_line(FILE *file)
{
    long pos = ftell(file);
    char ch;

    while((ch = fgetc(file)) != '\n')
        putchar(ch);
    
    printf("\n");

    fseek(file, pos, SEEK_SET);
}

void goto_next_line(FILE *file)
{
    char ch;
    while((ch = fgetc(file)) != '\n');
}

void goto_previous_line(FILE *file)
{   
    goto_start_line(file);
    if(ftell(file) <= 0)
        return;
    
    fseek(file, -2, SEEK_CUR);
    goto_start_line(file);
}

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

void goto_n_lines(FILE *file, int n, Direction d)
{
    switch(d)
    {
        case GOTO_NEXT:
            for(int i = 0; i < n; i++)
                goto_next_line(file);
                break;
        case GOTO_PREVIOUS:
            for(int i = 0; i < n; i++)
                goto_previous_line(file);
                break;
        default:
            printf("Dirección NO especificada\n");
            break;
    }
}