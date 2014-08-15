#include <stdio.h>
#include <malloc.h>
#include "Object.h"
#include "ObjectB.h"
#include "GarbageCollector.h"
#include "gc_free.h"

/**
 * User is recommended to prepare this example function to have a better experience on using garbage collector:
 *
 * objectBNew
 * ----------
 * This function creates an ObjectB object
 *
 * return:
 *  newObjectB  pointer that contains address of a newly created ObjectB
 */
ObjectB *objectBNew() {
  ObjectB *newObjectB = malloc(sizeof(ObjectB));
  newObjectB->reference = 0;
  newObjectB->flag = 0;
  newObjectB->free = objectBFree;
  newObjectB->ptrB1 = NULL; // user have to remember to assign all pointer(s) in the Object struct to NULL
  newObjectB->ptrB2 = NULL;
  
  return newObjectB;
}

/** 
 * User should at least prepare this example function in order to use garbage collector:
 *
 * objectBFree
 * -----------
 * This function walks through all the pointers in the object struct that prepared by user
 *
 * return:
 *  obj   object that gone through
 */
void objectBFree(Object *obj) {
  ((ObjectB *)obj)->ptrB1 = _gc_free((Object *)((ObjectB *)obj)->ptrB1);
  ((ObjectB *)obj)->ptrB2 = _gc_free((Object *)((ObjectB *)obj)->ptrB2);
}