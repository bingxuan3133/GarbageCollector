#ifndef ObjectA_H
#define ObjectA_H

#include "Object.h"

typedef struct ObjectA ObjectA;

struct ObjectA {
  int reference;
  int flag;
  void (*free)(Object *);
  ObjectA *ptrA;
};

void freeObjectA(Object *obj);

#endif // ObjectA_H
