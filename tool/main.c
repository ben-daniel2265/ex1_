#ifndef INCLUDED
#define INCLUDED

#include "AsciiArtTool.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


char invert_space_at(char character){
    if(character == ' '){
        return '@';
    }
    if(character == '@'){
        return ' ';
    }

    return character;
}

int main(int argc, char** argv){
    if(argc != 4){
        printf("gay");
        return 0;
    }

    FILE* file = fopen(argv[2], "r");
    RLEList list = AsciiArtRead(file);
    fclose(file);

    RLEListResult result;

    file = fopen(argv[3], "w");
    
    if(!strcmp(argv[1], "-i")){
        result = RLEListMap(list, invert_space_at);
        result = AsciiArtPrint(list, file);
    }
    else if(!strcmp(argv[1], "-e")){
        result = AsciiArtPrintEncoded(list, file);
    }
    else{
        printf("The flags can only be -e or -i");
    }

    fclose(file);

    /*if(!res){
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
    }*/

    RLEListDestroy(list);

    return 0;
}
#endif