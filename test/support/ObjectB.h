#ifndef ObjectB_H
#define ObjectB_H

#include "Object.h"

typedef struct ObjectB ObjectB;

struct ObjectB {
  int reference;
  int flag;
  void (*free)(Object *);
  Object *ptrB1;
  Object *ptrB2;
};

ObjectB *objectBNew();
void objectBFree(Object *obj);

#endif // ObjectB_H
