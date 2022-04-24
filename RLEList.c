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

/**
*   RLEListRemove: Removes a character found at a specified index in an RLE list.
*
* @param list - The RLE list to remove the character from.
* @param index - The index at which the character to be removed is found.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function.
* 	RLE_LIST_INDEX_OUT_OF_BOUNDS if given index is not withing the list's bounds.
* 	RLE_LIST_SUCCESS the character found at index has been removed successfully.
*/

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

/**
*   RLEListGet: Returns the character found at a specified index in an RLE list.
*
* @param list - The RLE list to retrieve the character from.
* @param index - The index at which the character to be retrieved is found.
* @param result - Pointer to be used to store the result of the operation, if it is NULL, the result will not be saved.
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as list.
* 	RLE_LIST_INDEX_OUT_OF_BOUNDS if given index is not withing the list's bounds.
* 	LIST_SUCCESS the character found at index has been retrieved successfully.
* @return
* 	0 if result is not RLE_LIST_SUCCESS.
* 	The character found at given index in case of success.
*/
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

/**
*   RLEListExportToString: Returns the characters found in an RLE list as a string.
*
* @param list - The RLE list to be exported as a string.
* @param result - Pointer to be used to store the result of the operation, if it is NULL, the result will not be saved.
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as list.
* 	LIST_SUCCESS the RLE list has been successfuly exported as a string.
* @return
* 	NULL if result is not RLE_LIST_SUCCESS.
* 	The string that corresponds to the received RLE list.
*/

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
/**
*   RLEListMap: Change the given RLE list's characters according to the received mapping function.
*               This function replaces each character of the give RLE list with its mapped character.
*
* @param list - The RLE list to edit.
* @param MapFunction - Pointer to a function of type MapFunction.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as a paramater.
* 	LIST_SUCCESS if the mapping is done successfully.
*/
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