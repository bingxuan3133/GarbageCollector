#include <stdio.h>
#include "Object.h"
#include "GarbageCollector.h"
#include "Flags.h"

void objectDump(Object *obj) {
  printf("%d:", obj->reference);
  if(getMarkBit(obj) == 1)
    printf("marked:");
  else
    printf("unmarked:");
  if(getKeepBit(obj) == 1)
    printf("kept\n");
  else
    printf("unkept\n");
}

Object *objectAssign(Object *obj) {
  obj->reference++;
  
  return obj;
}