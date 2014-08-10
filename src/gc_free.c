#include "gc_free.h"
#include "GarbageCollector.h"

/**
 * _gc_free
 * --------
 * This function acts as an extra layer of function calling (due to its testability on TDD stage)
 */
void *_gc_free(Object *obj) {
  return gc_free(obj);
}
