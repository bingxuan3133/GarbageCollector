#include <stdio.h>
#include <malloc.h>
#include "Object.h"
#include "ObjectA.h"
#include "GarbageCollector.h"
#include "gc_free.h"

ObjectA *objectANew() {
  ObjectA *newObjectA = malloc(sizeof(ObjectA));
  newObjectA->reference = 0;
  newObjectA->flag = 0;
  newObjectA->free = objectAFree;
  newObjectA->ptrA = NULL;
  
  return newObjectA;
}

void objectAFree(Object *obj) {
  if(((ObjectA *)obj)->ptrA != NULL) {
    ((ObjectA *)obj)->ptrA = _gc_free((Object *)((ObjectA *)obj)->ptrA);
  }
}