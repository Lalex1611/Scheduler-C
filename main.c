#include <stdio.h>
#include <stdlib.h>

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
    printf("%ld\n\n", sz);

    fseek(fp, -100, SEEK_END);
    int i = 0;
    while((ch = fgetc(fp)) != EOF && i < 1000)
    {
        putchar(ch);
        i++;
    }
    
    fclose(fp);

    return 0;
}