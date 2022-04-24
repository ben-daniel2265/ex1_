#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "RLEList.h"

typedef struct RLEList_t *RLEList;
typedef char (*MapFunction)(char);

/** Enum used for returning error codes from RLE list functions */

int str_expected_length(RLEList list);
int num_digits(int num);

RLEList RLEListCreate(){
    RLEList list = (RLEList)malloc(sizeof(*list));
    if(!list){
        return NULL;
    }
    list->data = NULL;
    list->appearances = NULL;
    list->next = NULL;

    return list;
}

void RLEListDestroy(RLEList list){
    if(!list){
        return;
    }
    while(list) {
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    }
}

RLEListResult RLEListAppend(RLEList list, char value){
    if(!list || !value){
        return RLE_LIST_NULL_ARGUMENT;
    }

    while(list->next){
        list = list->next;
    }
    if(list->data == value){
        list->appearances++;
        return RLE_LIST_SUCCESS;;
    }

    RLEList node = (RLEList)malloc(sizeof(*node));
    if(!node){
        return RLE_LIST_OUT_OF_MEMORY;
    }

    node->data = value;
    node->appearances = 1;
    node->next = NULL;
    list->next = node;

    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list){
    int count = 1;
    if(!list){
        return -1;
    }

    while(list->next != NULL){
        list = list->next;
        count++;
    }
    return count;
}

RLEListResult RLEListRemove(RLEList list, int index){
    if(!list || !index){
        return RLE_LIST_NULL_ARGUMENT;
    }
    int bounds = RLEListSize(list);
    if(index > bounds){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    for(int i = 0; i < index; i++){
        list = list->next;
    }
    list->next = list->next->next;
    return RLE_LIST_SUCCESS;
}


char RLEListGet(RLEList list, int index, RLEListResult *result){
    if(!list){
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }

    if(!(0 <= index && index < RLEListSize(list))){
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }


    while(index > 0){
        list = list->next;
        index -= 1;
    }

    *result = RLE_LIST_SUCCESS;
    return list->data;
}


int first_digit(int num){
    while(num >= 10){
        num = num / 10;
    }
    return num;
}

int str_expected_length(RLEList list){
    int length = 0;
    while(list){
        length += 2 + list->appearances;
        list = list->next;
    }
    return length;
}

int num_digits(int num){
    int count = 0;
    while(num > 9){
        num %= 10;
        count++;
    }
    return count;
}
char* RLEListExportToString(RLEList list, RLEListResult* result) {
    if (!list) {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    int string_len = str_expected_length(list);
    char* string = (char*)malloc((string_len+1) * sizeof(char));
    if(!string){
        *result = RLE_LIST_ERROR;
        return NULL;
    }
    char* temp_arr = string;
    while(list){
        *temp_arr = list->data;
        temp_arr++;
        sprintf(temp_arr, "%d", list->appearances);
        temp_arr += num_digits(list->appearances);
        *temp_arr = '\n';
        temp_arr++;
        list = list->next;

    }
    if(result != NULL){
        *result = RLE_LIST_SUCCESS;
    }
    return string;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if(!list){
        return RLE_LIST_NULL_ARGUMENT;
    }

    while(list){
        list->data = map_function(list->data);
        list = list->next;
    }

    return RLE_LIST_SUCCESS;
}
