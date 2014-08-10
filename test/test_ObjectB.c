#include <malloc.h>
#include "unity.h"
#include "GarbageCollector.h"
#include "mock_Flags.h"
#include "Object.h"
#include "ObjectB.h"
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
// Test objectBNew
//==================
void test_objectBNew_should_create_objectB_properly(void) {
  ObjectB *object = objectBNew();
  
  TEST_ASSERT_EQUAL(0, object->reference);
  TEST_ASSERT_EQUAL(0, object->flag);
  TEST_ASSERT_EQUAL_PTR(&objectBFree, object->free);
  
  free(object);
}

//==================
// Test objectBFree
//==================
/*
 *  ptr -> object1 -> object2
 */
void test_freeObjectB_walk_thru_object1_to_object2(void) {
	ObjectB *ptr;
  ObjectB object3 = {.reference = 1, .flag = 0, .free = objectBFree, .ptrB1 = NULL, .ptrB2 = NULL};
  ObjectB object2 = {.reference = 1, .flag = 0, .free = objectBFree, .ptrB1 = NULL, .ptrB2 = NULL};
  ObjectB object1 = {.reference = 1, .flag = 0, .free = objectBFree, .ptrB1 = (Object *)&object2, .ptrB2 = (Object *)&object3};

  ptr = &object1;
  gc_free = phase1Mark;

  _gc_free_ExpectAndReturn((Object *)&object2, &object2);
  _gc_free_ExpectAndReturn((Object *)&object3, &object3);
  
  _object_free((Object *)ptr);
}

