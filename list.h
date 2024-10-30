#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef union {
    int Int;
    double Double;
    char *Str;
    struct List *list;
} Value;


typedef enum {
    typeInt,
    typeDouble,
    typeStr,
    typeList
} Type;


typedef struct {
    Value value;
    Type type;
} Elem;


typedef struct List {
    Elem *sequence;
    void (*print)(Elem *);
    int len;
} List;


void printList(List *list);

void printElem(Elem *elem);

List *initList();

void freeList(List *list);

void append(List *list, Elem elem);

Elem pop(List *list, int index);

void extend(List *list, List *extList);

void insert(List *list, Elem elem, int index);
