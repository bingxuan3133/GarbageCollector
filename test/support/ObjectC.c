#include <stdio.h>
#include <malloc.h>
#include "Object.h"
#include "ObjectC.h"
#include "GarbageCollector.h"
#include "gc_free.h"

/**
 * User is recommended to prepare this example function to have a better experience on using garbage collector:
 *
 * objectCNew
 * ----------
 * This function creates an ObjectC object
 *
 * return:
 *  newObjectC  pointer that contains address of a newly created ObjectC
 */
ObjectC *objectCNew() {
  ObjectC *newObjectC = malloc(sizeof(ObjectC));
  newObjectC->reference = 0;
  newObjectC->flag = 0;
  newObjectC->free = objectCFree;
  newObjectC->ptrC1 = NULL; // user have to remember to assign all pointer(s) in the Object struct to NULL
  newObjectC->ptrC2 = NULL;
  newObjectC->ptrC3 = NULL;
  
  return newObjectC;
}

/** 
 * User should at least prepare this example function in order to use garbage collector:
 *
 * objectCFree
 * -----------
 * This function walks through all the pointers in the object struct that prepared by user
 *
 * return:
 *  obj   object that gone through
 */
void objectCFree(Object *obj) {
  ((ObjectC *)obj)->ptrC1 = _gc_free((Object *)((ObjectC *)obj)->ptrC1);
  ((ObjectC *)obj)->ptrC2 = _gc_free((Object *)((ObjectC *)obj)->ptrC2);
  ((ObjectC *)obj)->ptrC3 = _gc_free((Object *)((ObjectC *)obj)->ptrC3);
}