#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "AsciiArtTool.h"
#include "../RLEList.c"


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

RLEListResult AsciiArtPrint(RLEList list, FILE *out_stream){
    if(!list){
        return RLE_LIST_NULL_ARGUMENT;
    }

    int list_size = RLEListSize(list);
    char* out_string = (char*)malloc(sizeof(char)*list_size + 1);
    char* temp = out_string;
    int amount_in_node;

    while(list){
        amount_in_node = list->amount;
        while(amount_in_node){
            *temp = list->character;
            temp++;
            amount_in_node--;
        }
        list = list->next;
    }
    *temp = '\0';

    if(!fputs(out_string, out_stream)){
        free(out_string);
        return RLE_LIST_SUCCESS;
    }
    else{
        free(out_string);
        return RLE_LIST_ERROR;
    }
}

RLEListResult AsciiArtPrintEncoded(RLEList list, FILE *out_stream){
    if(!list){
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEListResult result;

    if(!fputs(RLEListExportToString(list, &result), out_stream)){
        return RLE_LIST_SUCCESS;
    }
    else{
        return RLE_LIST_ERROR;
    }
}
