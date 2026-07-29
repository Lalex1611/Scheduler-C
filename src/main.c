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
    goto_start_line(fp);
    read_line(fp);

    goto_n_lines(fp, 2, GOTO_PREVIOUS);
    read_line(fp);
    
    fclose(fp);

    return 0;
}