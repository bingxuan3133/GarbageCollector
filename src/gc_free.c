#include "gc_free.h"
#include "GarbageCollector.h"

void *_gc_free(Object *obj) {
  return gc_free(obj);
}
