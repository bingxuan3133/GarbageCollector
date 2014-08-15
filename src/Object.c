#include <stdio.h>
#include "Object.h"
#include "GarbageCollector.h"
#include "Flags.h"

/*
 * objectDump
 * ----------
 * This function printf reference number, flag statuses of an object
 */
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

/*
 * User have to use this function for every assignments in order to use garbage collector
 *
 * objectAssign
 * ------------
 * This function increases reference number by 1 when an object is assign to a pointer
 * 
 * input:
 *  obj   object that is to be assigned to a pointer
 * return:
 *  obj   address of object to be assigned
 */
Object *objectAssign(Object *obj) {
  obj->reference++;
  
  return obj;
}