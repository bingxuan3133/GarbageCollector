#ifndef Object_H
#define Object_H

typedef struct Object Object;

struct Object {
  int reference;
  int flag;
  void (*free)(Object *);
};

void dumpObject(Object *obj);

#endif // Object_H
