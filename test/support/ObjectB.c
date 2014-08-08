#include <stdio.h>
#include <malloc.h>
#include "Object.h"
#include "ObjectB.h"
#include "GarbageCollector.h"
#include "gc_free.h"

ObjectB *objectBNew() {
  ObjectB *newObjectB = malloc(sizeof(ObjectB));
  newObjectB->reference = 0;
  newObjectB->flag = 0;
  newObjectB->free = objectBFree;
  newObjectB->ptrB1 = NULL;
  newObjectB->ptrB2 = NULL;
  
  return newObjectB;
}

void objectBFree(Object *obj) {
  if(((ObjectB *)obj)->ptrB1 != NULL) {
    ((ObjectB *)obj)->ptrB1 = _gc_free((Object *)((ObjectB *)obj)->ptrB1);
  }
  
  if(((ObjectB *)obj)->ptrB2 != NULL) {
    ((ObjectB *)obj)->ptrB2 = _gc_free((Object *)((ObjectB *)obj)->ptrB2);
  }
}