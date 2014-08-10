#include <stdio.h>
#include <malloc.h>
#include "Object.h"
#include "ObjectB.h"
#include "GarbageCollector.h"
#include "gc_free.h"

/**
 * objectBNew
 * ----------
 * This function creates an ObjectB object
 */
ObjectB *objectBNew() {
  ObjectB *newObjectB = malloc(sizeof(ObjectB));
  newObjectB->reference = 0;
  newObjectB->flag = 0;
  newObjectB->free = objectBFree;
  newObjectB->ptrB1 = NULL;
  newObjectB->ptrB2 = NULL;
  
  return newObjectB;
}

/** 
 * User should at least prepare this example function in order to use garbage collector:
 *
 * objectBFree
 * -----------
 * This function walks through all the pointers in the object struct that prepared by user
 */
void objectBFree(Object *obj) {
  ((ObjectB *)obj)->ptrB1 = _gc_free((Object *)((ObjectB *)obj)->ptrB1);
  ((ObjectB *)obj)->ptrB2 = _gc_free((Object *)((ObjectB *)obj)->ptrB2);
}