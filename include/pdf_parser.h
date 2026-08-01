#include "file.h"

typedef enum
{
    PDF_TRAILER,
    PDF_STARTXREF,
    PDF_XREF
} PdfPart;

typedef struct
{
    FILE *file;
    int limit;
    PdfPart type;
} FindTrailerOpts;

int find_trailerX(FindTrailerOpts opts);

#define find_trailer(...) \
    find_trailerX((FindTrailerOpts){.limit = 100, .type = PDF_TRAILER, __VA_ARGS__})

