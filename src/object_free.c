#include "object_free.h"
#include "Object.h"

void _object_free(Object *obj) {
  obj->free(obj);
}
