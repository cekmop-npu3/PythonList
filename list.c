#include "list.h"


void printList(List *list){
    if (list){
        if (list->sequence && list->len > 0){
            printf("List(");
            list->print(&list->sequence[0]);
            for (int i = 1; i < list->len; i++){
                printf(", ");
                list->print(&list->sequence[i]);
            }
            printf(")");
        }
        else
            printf("List()");
    }
}


void printElem(Elem *elem){
    switch (elem->type){
        case typeInt:
            printf("%d", elem->value.Int);
            break;
        case typeDouble:
            printf("%.2f", elem->value.Double);
            break;
        case typeStr:
            printf("%s", elem->value.Str);
            break;
        case typeList:
            printList(elem->value.list);
            break;
        } 
}


List *initList(){
    List *list = malloc(sizeof(List));
    if (!list)
        return NULL;
    list->len = 0;
    list->sequence = NULL;
    list->print = printElem;
    return list;
}


void freeList(List *list){
    if (list){
        if (list->sequence){
            for (int i = 0; i < list->len; i++)
                switch (list->sequence[i].type){
                    case typeStr:
                        free(list->sequence[i].value.Str);
                        break;
                    case typeList:
                        freeList(list->sequence[i].value.list);
                        break;
                }
            free(list->sequence);
        }
        free(list);
    }
}


void append(List *list, Elem elem){
    Elem *tmpSequence = realloc(list->sequence, (++list->len) * sizeof(Elem));
    if (tmpSequence){
        list->sequence = tmpSequence;
        list->sequence[list->len - 1] = elem;
    }
}


Elem pop(List *list, int index){
    if (index >= 0 && index < list->len){
        Elem *tmpSequence = calloc(--list->len, sizeof(Elem));
        if (tmpSequence){
            int newArrIndex = 0;
            Elem poppedElem;
            for (int i = 0; i < list->len + 1; i++){
                if (i != index){
                    tmpSequence[newArrIndex] = list->sequence[i];
                    newArrIndex++;
                }
                else
                    poppedElem = list->sequence[i];
            }
            free(list->sequence);
            list->sequence = tmpSequence;
            return poppedElem;
        }
    }
}


void extend(List *list, List *extList){
    Elem *tmpSequence = realloc(list->sequence, (list->len + extList->len) * sizeof(double));
    if (tmpSequence) {
        int start = list->len;
        list->len += extList->len;
        for (int i = start; i < list->len; i++)
            tmpSequence[i] = extList->sequence[i - start];
        list->sequence = tmpSequence;
    }
}


void insert(List *list, Elem elem, int index){
    if (index >= 0 && index <= list->len){
        Elem *tmpSequence = calloc(++list->len, sizeof(double));
        if (tmpSequence){
            int padIndex = 0;
            for (int i = 0; i < list->len; i++){
                if (i == index){
                    tmpSequence[i] = elem;
                    padIndex++;
                }
                else
                    tmpSequence[i] = list->sequence[i - padIndex];
            }
            free(list->sequence);
            list->sequence = tmpSequence;
        }
    }
}
