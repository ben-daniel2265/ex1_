#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "RLEList.h"

typedef struct RLEList_t{
    char character;
    int amount;
    struct RLEList_t* next;
} *RLEList;

typedef char (*MapFunction)(char);
int str_expected_length(RLEList list);
int num_digits(int num);

RLEList RLEListCreate(){
    RLEList list = (RLEList)malloc(sizeof(*list));
    if(!list){
        return NULL;
    }
    list->character = NULL;
    list->amount = NULL;
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

    if(list->character == value){
        list->amount++;
        return RLE_LIST_SUCCESS;
    }

    RLEList node = (RLEList)malloc(sizeof(*node));
    if(!node){
        return RLE_LIST_OUT_OF_MEMORY;
    }

    node->character = value;
    node->amount = 1;
    node->next = NULL;
    list->next = node;

    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list){
    int count = 0;
    if(!list){
        return -1;
    }

    while(list){
        count += list->amount;
        list = list->next;
    }
    return count;
}

RLEListResult RLEListRemove(RLEList list, int index){
    if(!list){
        return RLE_LIST_NULL_ARGUMENT;
    }

    if(!(0 <= index && index < RLEListSize(list))){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    int amount_in_node;
    RLEList previous_node = NULL;

    while(index > 0){
        amount_in_node = list->amount;
        while(amount_in_node && index){
            amount_in_node -= 1;
            index -= 1;
        }

        if(index >= 0 && amount_in_node == 0){
            previous_node = list;
            list = list->next;

        }
    }

    RLEList temp;
    list->amount -= 1;
    if(!(list->amount)){
        if(list->next){
            list->amount = list->next->amount;
            list->character = list->next->character;

            temp = list->next;
            list->next = list->next->next;
            free(temp);

            if(previous_node->character == list->character){
                previous_node->amount = previous_node->amount + list->amount;
                previous_node->next = list->next;
                free(list);
            }
        }
        else{
            free(list);
            previous_node->next = NULL;
        }
    }

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

    int amount_in_node;
    while(index > 0){
        amount_in_node = list->amount;
        while(amount_in_node && index){
            amount_in_node -= 1;
            index -= 1;
        }

        if(index >= 0){
            list = list->next;
        }
    }

    *result = RLE_LIST_SUCCESS;
    return list->character;
}

int num_digits(int num){
    int count = 1;
    while(num > 9){
        num %= 10;
        count++;
    }
    return count;
}

int str_expected_length(RLEList list){
    int length = 0;
    while(list){
        length += 2 + num_digits(list->amount);
        list = list->next;
    }
    return length;
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
        *temp_arr = list->character;
        temp_arr++;

        sprintf(temp_arr, "%d", list->amount);
        temp_arr += num_digits(list->amount);
    
        *temp_arr = '\n';
        temp_arr++;

        list = list->next;
    }

    if(result != NULL){
        *result = RLE_LIST_SUCCESS;
    }

    *temp_arr = '\0';

    return string;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if(!list){
        return RLE_LIST_NULL_ARGUMENT;
    }

    while(list){
        list->character = map_function(list->character);
        list = list->next;
    }

    return RLE_LIST_SUCCESS;
}