#include <stdio.h>
#include <malloc.h>
#include "Object.h"
#include "ObjectA.h"
#include "GarbageCollector.h"
#include "gc_free.h"

/**
 * User is recommended to prepare this example function to have a better experience on using garbage collector:
 *
 * objectANew
 * ----------
 * This function creates an ObjectA object
 *
 * return:
 *  newObjectA  pointer that contains address of a newly created ObjectA
 */
ObjectA *objectANew() {
  ObjectA *newObjectA = malloc(sizeof(ObjectA));
  newObjectA->reference = 0;
  newObjectA->flag = 0;
  newObjectA->free = objectAFree;
  newObjectA->ptrA = NULL;  // user have to remember to assign all pointer(s) in the Object struct to NULL
  
  return newObjectA;
}

/** 
 * User should at least prepare this example function in order to use garbage collector:
 *
 * objectAFree
 * -----------
 * This function walks through all the pointers in the object struct that prepared by user
 *
 * return:
 *  obj   object that gone through
 */
void objectAFree(Object *obj) {
  ((ObjectA *)obj)->ptrA = _gc_free((Object *)((ObjectA *)obj)->ptrA);
}

