#ifndef LIST_H
#define LIST_H
#include <stdlib.h>

typedef struct LIST_STRUCT{
    void** items;
    size_t size;
    size_t itemSize;
} listT;

listT* initList(size_t itemSize);

void listPush(listT* list, void* item);

#endif