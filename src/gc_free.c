#include "gc_free.h"
#include "GarbageCollector.h"

void _gc_free(Object *obj) {
  gc_free(obj);
}
