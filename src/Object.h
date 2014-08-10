#ifndef Object_H
#define Object_H

/** 
 * User should include this 3 elements (with correct sequence) at the top in any struct of the object they wanted to create:
 *
 * int reference;
 * int flag;
 * void (*free)(Object *);
 */

/** 
 * This is the general Object struct
 */

typedef struct Object Object;
 
struct Object {
  int reference;
  int flag;
  void (*free)(Object *);
};

void objectDump(Object *obj);
Object *objectAssign(Object *obj);

#endif // Object_H
