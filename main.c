//
// Created by Yonatan Elbaz on 26/04/2022.
//

#include "RLEList.c"

int main(){
    RLEList list = RLEListCreate();
    list->amount = 1;

    char in;
    scanf("%c", &in);
    list->character = in;

    for(int i = 0; i < 10; i ++){
        scanf("%c", &in);
        RLEListAppend(list, in);
    }

    RLEListResult res;
    printf("%s", RLEListExportToString(list, &res));

    RLEListRemove(list, 6);

    printf("gae\n%s", RLEListExportToString(list, &res));

    return 0;
}