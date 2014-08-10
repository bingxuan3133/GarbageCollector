#include "Flags.h"

/**
 * setMarkBit
 * ----------
 * This function set an object as marked
 */
void setMarkBit(Object *obj) {
  obj->flag |= MARK;
}

/**
 * clearMarkBit
 * ------------
 * This function set an object as unmarked
 */
void clearMarkBit(Object *obj) {
  obj->flag &= ~MARK;
}

/**
 * setKeepStartBit
 * ---------------
 * This function set an object as kept and indicate it is the starting point of keeping objects
 */
void setKeepStartBit(Object *obj) {
  obj->flag |= KEEPSTART;
}

/**
 * clearKeepStartBit
 * -----------------
 * This function set an object as unkept
 */
void clearKeepStartBit(Object *obj) {
  obj->flag &= ~KEEPSTART;
}

/**
 * setKeepFollowBit
 * ----------------
 * This function set an object as kept and indicate it is after the starting point of keeping objects
 */
void setKeepFollowBit(Object *obj) {
  obj->flag |= KEEPFOLLOW;
}

/**
 * clearKeepFollowBit
 * ------------------
 * This function set an object as unkept
 */
void clearKeepFollowBit(Object *obj) {
  obj->flag &= ~KEEPFOLLOW;
}