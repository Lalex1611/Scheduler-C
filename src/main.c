#include "../include/file.h"
#include "../include/pdf_parser.h"

int main()
{

    FILE *fp = fopen("./files/8_ISTE_Horarios-2026-2.pdf", "rb");

    if(fp == NULL)
    {
        printf("Unable to open the file\n");
        return 1;
    }

    print_size(get_size(fp), KB);
    if(!find_trailer(fp))
        printf("Yeeepii\n");

    fclose(fp);

    return 0;
}