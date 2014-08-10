#ifndef ObjectB_H
#define ObjectB_H

#include "Object.h"

typedef struct ObjectB ObjectB;

/** 
 * User should include this 3 elements (with correct sequence) at the top in any struct of the object they wanted to create:
 *
 * int reference;
 * int flag;
 * void (*free)(Object *);
 */

/** 
 * This is an example of ObjectB struct
 */
struct ObjectB {
  int reference;
  int flag;
  void (*free)(Object *);
  Object *ptrB1;
  Object *ptrB2;
};

ObjectB *objectBNew();
void objectBFree(Object *obj);

#endif // ObjectB_H