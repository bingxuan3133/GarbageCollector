#include "Flags.h"

void setMarkBit(Object *obj) {
  obj->flag |= MARK;
}

void clearMarkBit(Object *obj) {
  obj->flag &= ~MARK;
}

void setKeepStartBit(Object *obj) {
  obj->flag |= KEEPSTART;
}

void clearKeepStartBit(Object *obj) {
  obj->flag &= ~KEEPSTART;
}

void setKeepFollowBit(Object *obj) {
  obj->flag |= KEEPFOLLOW;
}

void clearKeepFollowBit(Object *obj) {
  obj->flag &= ~KEEPFOLLOW;
}