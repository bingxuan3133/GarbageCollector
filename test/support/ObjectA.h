#ifndef ObjectA_H
#define ObjectA_H

#include "Object.h"

typedef struct ObjectA ObjectA;

struct ObjectA {
  int reference;
  int flag;
  void (*free)(Object *);
  Object *ptrA;
};

ObjectA *objectANew();
void objectAFree(Object *obj);

#endif // ObjectA_H
