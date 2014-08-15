#include "Flags.h"

/**
 * setMarkBit
 * ----------
 * This function set an object as marked
 * 
 * input:
 *  obj   object to be marked
 */
void setMarkBit(Object *obj) {
  obj->flag |= MARK;
}

/**
 * clearMarkBit
 * ------------
 * This function set an object as unmarked
 * 
 * input:
 *  obj   object to be unmarked
 */
void clearMarkBit(Object *obj) {
  obj->flag &= ~MARK;
}

/**
 * setKeepStartBit
 * ---------------
 * This function set an object as kept and indicate it is the starting point of keeping objects
 * 
 * input:
 *  obj   object to be kept (starting object)
 */
void setKeepStartBit(Object *obj) {
  obj->flag |= KEEPSTART;
}

/**
 * clearKeepStartBit
 * -----------------
 * This function set an object as unkept
 * 
 * input:
 *  obj   object to be unkept (starting object)
 */
void clearKeepStartBit(Object *obj) {
  obj->flag &= ~KEEPSTART;
}

/**
 * setKeepFollowBit
 * ----------------
 * This function set an object as kept and indicate it is after the starting point of keeping objects
 * 
 * input :
 *  obj   object to be kept (following object)
 */
void setKeepFollowBit(Object *obj) {
  obj->flag |= KEEPFOLLOW;
}

/**
 * clearKeepFollowBit
 * ------------------
 * This function set an object as unkept
 * 
 * input :
 *  obj   object to be unkept (following object)
 */
void clearKeepFollowBit(Object *obj) {
  obj->flag &= ~KEEPFOLLOW;
}