#include "unity.h"
#include "GarbageCollector.h"
#include "mock_Flags.h"
#include "Object.h"
#include "ObjectA.h"
#include "object_free.h"
#include "mock_gc_free.h"
#include "mock_free.h"

void setUp(void)
{
}

void tearDown(void)
{
}

//==================
// Test freeObjectA
//==================
/*
 *  ptr -> object
 */
void test_freeObjectA_will_not_walk_to_NULL(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 1, .flag = 0, .free = freeObjectA, .ptrA = NULL};

  ptr = &object;
  gc_free = phase1Mark;
  
  // Test object before recursion
  
  _object_free((Object *)ptr);
}

/*
 *  ptr -> object1 -> object2
 */
void test_freeObjectA_walk_thru_object1_to_object2(void) {
	ObjectA *ptr;
  ObjectA object2 = {.reference = 1, .flag = 0, .free = freeObjectA, .ptrA = NULL};
  ObjectA object1 = {.reference = 1, .flag = 0, .free = freeObjectA, .ptrA = &object2};

  ptr = &object1;
  gc_free = phase1Mark;
  
  // Test object before recursion
  _gc_free_Expect((Object *)&object2);
  
  _object_free((Object *)ptr);
}
