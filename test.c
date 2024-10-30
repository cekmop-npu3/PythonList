#include <stdlib.h>
#include "list.h"


int main(){
    List *list = initList();
    Elem elem = {
        .value.Int = 12,
        .type = typeInt
    };
    Elem elem2 = {
        .value.Str = malloc((strlen("qwerty") + 1) * sizeof(char)),
        .type = typeStr
    };
    strcpy(elem2.value.Str, "qwerty");
    Elem insertElem = {
        .value.Double = 12.3,
        .type = typeDouble
    };
    append(list, elem);
    append(list, elem2);
    insert(list, insertElem, 0);
    printList(list);
    printf("\n");
    pop(list, 0);
    printList(list);
    freeList(list);
    return EXIT_SUCCESS;
}
