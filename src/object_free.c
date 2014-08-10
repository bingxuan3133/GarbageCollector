#include "object_free.h"
#include "Object.h"

/* _object_free
 * ------------
 * This function acts as an extra layer of function calling (due to its testability on TDD stage)
 */
void _object_free(Object *obj) {
  obj->free(obj);
}
