#include <stdio.h>
#include "Object.h"
#include "ObjectA.h"
#include "GarbageCollector.h"
#include "gc_free.h"

void freeObjectA(Object *obj) {
  if(((ObjectA *)obj)->ptrA != NULL) {
    _gc_free((Object *)((ObjectA *)obj)->ptrA);
  }
}