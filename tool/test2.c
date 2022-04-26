#include "AsciiArtTool.c"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../RLEList.h"


int main(int argc, char** argv){
    if(argc != 2){
        printf("gay");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    RLEList list = AsciiArtRead(file);
    fclose(file);

    RLEListResult res;

    printf("%s", RLEListExportToString(list, &res));
    printf("%d\n", res);

    file = fopen("out.txt", "w");
    res = AsciiArtPrint(list, file);
    fclose(file);
    if(!res){
        printf("printed good ;P\n");
    }
    else{
        printf("printed bad :'(\n");
        printf("%d\n", res);
    }

    file = fopen("encoded_out.txt", "w");
    res = AsciiArtPrintEncoded(list, file);
    fclose(file);
    if(!res){
        printf("printed encoded good ;P\n");
    }
    else{
        printf("printed encoded bad :'(\n");
        printf("%d\n", res);
    }

    RLEListDestroy(list);

    return 0;
}