#include <stdio.h>
#include "GarbageCollector.h"
#include "Flags.h"
#include "Object.h"
#include "object_free.h"
#include "free.h"
#include "gc_free.h"

int previousKeepBit;         // indicates if there is a object kept before along a single route
void *(*gc_free)(Object *);  // function pointer to run 3 phases of garbage collecting

/**
 * freeObject
 * ----------
 * This is the main function which will called by user for garbage collecting object that wanted to be freed
 *
 * input:
 *  obj     object that is going to be free (or not free depends on its condition)
 */
void freeObject(Object *obj) {
  previousKeepBit = 0;

  gc_free = phase1Mark;
  _gc_free((Object *)obj);
  gc_free = phase2Mark;
  _gc_free((Object *)obj);
  gc_free = phase3Sweep;
  _gc_free((Object *)obj);
}

/**
 * phase1Mark
 * ----------
 * This function will reduce references number and clear keep flag (left by previous phase3Sweep()) of an object
 *
 * input:
 *  obj     object that on going phase1Mark
 * output:
 *  NULL    if on going object is a NULL
 *  obj     if on going object is non-NULL
 */
void *phase1Mark(Object *obj) {
  if(obj == NULL) return NULL;

  obj->reference--; // reduce reference by 1 when just enter an object

  if(getMarkBit(obj) == 1) {  // do nothing if object is marked
    return obj;
  } else {                    // keep going on if object is unmarked
    setMarkBit(obj);
    clearKeepStartBit(obj);
    clearKeepFollowBit(obj);
    _object_free(obj);
    clearMarkBit(obj);
  }

  return obj;
}

/**
 * phase2Mark
 * ----------
 * This function will select which objects should be kept
 *
 * input:
 *  obj     object that on going phase2Mark
 * output:
 *  NULL    if on going object is a NULL
 *  obj     if on going object is non-NULL
 */
void *phase2Mark(Object *obj) {
  if(obj == NULL) return NULL;

  if(previousKeepBit == 1) {      // keep object as KEEPFOLLOW if it is after a KEEPSTART object
    setKeepFollowBit(obj);
  } else if(obj->reference > 0) { // keep object as KEEPSTART if its reference number is more than 0
    setKeepStartBit(obj);
    previousKeepBit = 1;
  }

  if(getMarkBit(obj) == 1) {      // do nothing if marked
    return obj;
  } else {                        // keep going on if object is unmarked
    setMarkBit(obj);
    _object_free(obj);
    clearMarkBit(obj);
  }

  if(getKeepStartBit(obj) == 1 && getKeepFollowBit(obj) == 0)
    previousKeepBit = 0;          // clear previousKeepBit when returning from KEEPSTART object

  return obj;
}

/**
 * phase3Sweep
 * -----------
 * This function will decide which object should be kept
 *
 * input:
 *  obj     object that on going phase2Mark
 * output:
 *  NULL    if the object is a NULL or freed
 *  obj     if the object is non-NULL or cannot be freed
 */
void *phase3Sweep(Object *obj) {
  void *old;

  if(obj == NULL) return NULL;

  if(getKeepBit(obj) == 1) {
    previousKeepBit = 1;
  } else if(previousKeepBit == 1 && getKeepBit(obj) == 0) {
    setKeepFollowBit(obj);
  }

  if(getMarkBit(obj) == 1) {  // increase reference number by 1 even though revisit marked object
    if(getKeepBit(obj) == 1)
      obj->reference++;
    return obj;
  } else {                    // keep going on if object is unmarked
    setMarkBit(obj);
    _object_free(obj);
    clearMarkBit(obj);
  }

  if(getKeepBit(obj) == 1) {  // increase reference number for kept object when returning
    obj->reference++;
    if(getKeepStartBit(obj) == 1) {
      previousKeepBit = 0;
    }
  } else { // before freeing an object, the program will go through all the pointers in the object struct to reduce their reference number by 1
    old = gc_free;
    gc_free = reduceReference;
    _object_free(obj);
    gc_free = old;

    _free(obj);

    return NULL;
  }

  return obj;
}

/**
 * reduceReference
 * -----------
 * This function is used by phase3Sweep to reduce the reference number of an object
 *
 * input:
 *  obj     object that planned to reduce its reference number
 * output:
 *  NULL    if on going object is a NULL
 *  obj     if on going object is non-NULL
 */
void *reduceReference(Object *obj) {
  if(obj == NULL) return NULL;

  if(getKeepBit(obj))
    obj->reference--;
  return obj;
}