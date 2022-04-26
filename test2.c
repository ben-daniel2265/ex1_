#include "AsciiArtTool.c"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "RLEList.c"


int main(int argc, char** argv){
    if(argc != 2){
        printf("gay");
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    RLEList list = AsciiArtRead(input);
    RLEListResult res;

    printf("%s", RLEListExportToString(list, &res));

    RLEListDestroy(list);
    fclose(input);

    return 0;
}