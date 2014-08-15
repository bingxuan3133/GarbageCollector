#ifndef Flags_H
#define Flags_H

#include "Object.h"

#define MARK 1        // indicates object is visited before
#define KEEPSTART 2   // indicates object should be keep and it is the first object to be kept in a single route/branch
#define KEEPFOLLOW 4  // indicates object should be keep due to its reference is kept

/*
 * This macro get MARK flag from an object
 *
 * input:
 *  x   object to get MARK flag from
 * return:
 *  0   object is unmarked
 *  1   object is marked
 */
#define getMarkBit(x) ((x)->flag & MARK)

/*
 * This macro get KEEPSTART flag from an object
 *
 * input:
 *  x   object to get KEEPSTART flag from
 * return:
 *  0   object is unkept (keep starter object)
 *  1   object is kept (keep starter object)
 */
#define getKeepStartBit(x) ((x)->flag & KEEPSTART) >> 1

/*
 * This macro get KEEPFOLLOW flag from an object
 *
 * input:
 *  x   object to get KEEPFOLLOW flag from
 * return:
 *  0   object is unkept (keep follower object)
 *  1   object is kept (keep follower object)
 */
#define getKeepFollowBit(x) ((x)->flag & KEEPFOLLOW) >> 2

/*
 * This macro get KEEP flag (either KEEPSTART or KEEPFOLLOW) from an object
 *
 * input:
 *  x   object to get KEEP flag from
 * return:
 *  0   object is unkept
 *  1   object is kept
 */
#define getKeepBit(x) getKeepStartBit(x) | getKeepFollowBit(x)

void setMarkBit(Object *obj);
void clearMarkBit(Object *obj);

void setKeepStartBit(Object *obj);
void clearKeepStartBit(Object *obj);

void setKeepFollowBit(Object *obj);
void clearKeepFollowBit(Object *obj);

#endif // Flags_H
