#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "AsciiArtTool.h"


RLEList AsciiArtRead(FILE* in_stream){
    RLEList list = RLEListCreate();
    RLEListResult result;
    char charecter;
    int err = fscanf(in_stream, "%c", &charecter);

    while(err != EOF && !result){
        result = RLEListAppend(list, charecter);
        err = fscanf(in_stream, "%c", &charecter);
    }

    return list;
}

RLEListResult AsciiArtPrint(RLEList list, FILE *out_stream);

RLEListResult AsciiArtPrintEncoded(RLEList list, FILE *out_stream);
