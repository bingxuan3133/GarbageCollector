#include <stdio.h>
#include <malloc.h>
#include "Object.h"
#include "ObjectA.h"
#include "GarbageCollector.h"
#include "gc_free.h"

/**
 * objectANew
 * ----------
 * This function creates an ObjectA object
 */
ObjectA *objectANew() {
  ObjectA *newObjectA = malloc(sizeof(ObjectA));
  newObjectA->reference = 0;
  newObjectA->flag = 0;
  newObjectA->free = objectAFree;
  newObjectA->ptrA = NULL;
  
  return newObjectA;
}

/** 
 * User should at least prepare this example function in order to use garbage collector:
 *
 * objectAFree
 * -----------
 * This function walks through all the pointers in the object struct that prepared by user
 */
void objectAFree(Object *obj) {
  ((ObjectA *)obj)->ptrA = _gc_free((Object *)((ObjectA *)obj)->ptrA);
}

