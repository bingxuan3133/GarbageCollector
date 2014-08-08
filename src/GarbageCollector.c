#include <stdio.h>
#include "GarbageCollector.h"
#include "Flags.h"
#include "Object.h"
#include "object_free.h"
#include "free.h"
#include "gc_free.h"

int previousKeepBit;
void *(*gc_free)(Object *);

/*
 * Algorithm changes:
 *  1) Visit the object even though it has been marked
 *  2) Only decide to continue walk through or not after checking the object's MARK status when visiting it
 */

void *phase1Mark(Object *obj) {
  if(obj == NULL) return NULL;

  obj->reference--;
 
  if(getMarkBit(obj) == 1) {
    return obj;
  } else {
    setMarkBit(obj);
    clearKeepStartBit(obj);
    clearKeepFollowBit(obj);
    _object_free(obj);
    clearMarkBit(obj);
  }
  
  return obj;
}

/*
 *
 * obj1 -> obj2 
 *
 * both reference is reduced to 1, obj1 will become KEEPSTART, obj2 will become KEEPFOLLOW even though its reference is not zero
 *
 */
void *phase2Mark(Object *obj) {
  if(obj == NULL) return NULL;

  if(previousKeepBit == 1) {
    setKeepFollowBit(obj);
  } else if(obj->reference > 0) {
    setKeepStartBit(obj);
    previousKeepBit = 1;
  }

  if(getMarkBit(obj) == 1) {
    return obj;
  } else {
    setMarkBit(obj);
    _object_free(obj);
    clearMarkBit(obj);
  }
  
  if(getKeepStartBit(obj) == 1 && getKeepFollowBit(obj) == 0)
    previousKeepBit = 0;
  
  return obj;
}

void *phase3Sweep(Object *obj) {
  void *old;

  if(obj == NULL) return NULL;

  if(getKeepBit(obj) == 1) {
    previousKeepBit = 1;
  } else if(previousKeepBit == 1 && getKeepBit(obj) == 0) {
    setKeepFollowBit(obj);
  }

  if(getMarkBit(obj) == 1) {
    if(getKeepBit(obj) == 1)
    obj->reference++;
    return obj;
  } else {
    setMarkBit(obj);
    _object_free(obj);
    clearMarkBit(obj);
  }

  if(getKeepBit(obj) == 1) {
    obj->reference++;
    if(getKeepStartBit(obj) == 1) {
      previousKeepBit = 0;
    }
  } else {
    old = gc_free;
    gc_free = reduceReference;
    _object_free(obj);
    gc_free = old;
    
    _free(obj);

    return NULL;
  }

  return obj;
}

void *reduceReference(Object *obj) {
  if(obj == NULL) return NULL;  
  
  if(getKeepBit(obj))
    obj->reference--;
  return obj;
}