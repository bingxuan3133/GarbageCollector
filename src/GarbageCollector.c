#include <stdio.h>
#include "GarbageCollector.h"
#include "Flags.h"
#include "Object.h"
#include "object_free.h"
#include "free.h"

int previousKeepBit;
void (*gc_free)(Object *);

/*
 * Algorithm changes:
 *  1) Visit the object even though it has been marked
 *  2) Only decide to continue walk through or not after checking the object's MARK status when visiting it
 */

void phase1Mark(Object *obj) {
  obj->reference--;
  
  printf("%p\n", obj);
  
  if(getMarkBit(obj) == 1) {
    return;
  } else {
    setMarkBit(obj);
    _object_free(obj);
    clearMarkBit(obj);
  }
}

/*
 *
 * obj1 -> obj2 
 *
 * both reference is reduced to 1, obj1 will become KEEPSTART, obj2 will become KEEPFOLLOW even though its reference is not zero
 *
 */
void phase2Mark(Object *obj) {
  if(previousKeepBit == 1) {
    setKeepFollowBit(obj);
  } else if(obj->reference > 0) {
    setKeepStartBit(obj);
    previousKeepBit = 1;
  }

  if(getMarkBit(obj) == 1) {
    return;
  } else {
    setMarkBit(obj);
    _object_free(obj);
    clearMarkBit(obj);
  }
  
  if(getKeepStartBit(obj) == 1 && getKeepFollowBit(obj) == 0)
    previousKeepBit = 0;
}

void phase3Sweep(Object *obj) {
  if(getMarkBit(obj) == 1) {
    return;
  } else {
    setMarkBit(obj);
    _object_free(obj);
    clearMarkBit(obj);
  }
  
  if(getKeepBit(obj) == 1) {
    obj->reference++;
    if(getKeepStartBit(obj) == 1) {
      clearKeepStartBit(obj);
      previousKeepBit = 0;
    } else if(getKeepFollowBit(obj) == 1) {
      clearKeepFollowBit(obj);
    }
  } else {
    _free(obj);
  }
}