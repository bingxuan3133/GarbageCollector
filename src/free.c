#include <malloc.h>
#include "free.h"

/**
 * _free
 * -----
 * This function acts as an extra layer of function calling (due to its testability on TDD stage)
 */
void _free(void *obj) {
  free(obj);
}
