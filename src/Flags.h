#ifndef Flags_H
#define Flags_H

#include "Object.h"

#define MARK 1
#define KEEPSTART 2
#define KEEPFOLLOW 4

#define getMarkBit(x) ((x)->flag & MARK)
#define getKeepStartBit(x) ((x)->flag & KEEPSTART) >> 1
#define getKeepFollowBit(x) ((x)->flag & KEEPFOLLOW) >> 2
#define getKeepBit(x) getKeepStartBit(x) | getKeepFollowBit(x)

void setMarkBit(Object *obj);
void clearMarkBit(Object *obj);

void setKeepStartBit(Object *obj);
void clearKeepStartBit(Object *obj);

void setKeepFollowBit(Object *obj);
void clearKeepFollowBit(Object *obj);

#endif // Flags_H
