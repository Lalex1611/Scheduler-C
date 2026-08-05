#include "../include/file.h"
#include "../include/pdf_parser.h"

int main()
{

    FILE *fp = fopen("./files/8_ISTE_Horarios-2026-2.pdf", "rb");
    //FILE *fp = fopen("files/Avance de actividades en el SS profesional - 4.pdf", "rb");

    if(fp == NULL)
    {
        printf("Unable to open the file\n");
        return 1;
    }

    print_size(get_size(fp), KB);

    int xref = get_root(fp);
    printf("Numero de objeto de Root: %d\n", xref);

    long int table = get_obj_offset(fp, xref);

    fseek(fp, table, SEEK_SET);
    read(fp, LINE);
    fclose(fp);

    return 0;
}