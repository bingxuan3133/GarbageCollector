#ifndef ObjectC_H
#define ObjectC_H

#include "Object.h"

typedef struct ObjectC ObjectC;

/** 
 * User should include this 3 elements (with correct sequence) at the top in any struct of the object they wanted to create:
 *
 * int reference;
 * int flag;
 * void (*free)(Object *);
 */

/** 
 * This is an example of ObjectC struct
 */
struct ObjectC {
  int reference;
  int flag;
  void (*free)(Object *);
  Object *ptrC1;
  Object *ptrC2;
  Object *ptrC3;
};

ObjectC *objectCNew();
void objectCFree(Object *obj);

#endif // ObjectC_H