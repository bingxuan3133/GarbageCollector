#ifndef ObjectA_H
#define ObjectA_H

#include "Object.h"

typedef struct ObjectA ObjectA;

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
struct ObjectA {
  int reference;
  int flag;
  void (*free)(Object *);
  Object *ptrA;
};

ObjectA *objectANew();
void objectAFree(Object *obj);

#endif // ObjectA_H
