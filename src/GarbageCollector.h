#ifndef GarbageCollector_H
#define GarbageCollector_H

#include "Object.h"

extern int previousKeepBit;
extern void *(*gc_free)(Object *);

void freeObject(Object *obj);

void *phase1Mark(Object *obj);
void *phase2Mark(Object *obj);
void *phase3Sweep(Object *obj);

void *reduceReference(Object *obj);

#endif // GarbageCollector_H
