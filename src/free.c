#include <malloc.h>
#include "free.h"

void _free(void *obj) {
  free(obj);
}
