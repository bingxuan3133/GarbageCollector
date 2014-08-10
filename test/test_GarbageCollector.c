#include <stdio.h>
#include "unity.h"
#include "GarbageCollector.h"
#include "mock_Flags.h"
#include "Object.h"
#include "ObjectA.h"
#include "gc_free.h"
#include "mock_object_free.h"
#include "mock_free.h"

void setUp(void)
{
}

void tearDown(void)
{
}

//=========
// ObjectA
//=========

//=================
// Test phase1Mark
//=================
/*
 *  ptr -> object
 */
void test_phase1Mark_given_reference_is_1_should_reduce_reference_to_0(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 1, .flag = 0, .free = objectAFree, .ptrA = NULL};

  ptr = &object;
  gc_free = phase1Mark;
  
  // Mocking
  setMarkBit_Expect((Object *)&object);
  clearKeepStartBit_Expect((Object *)&object);
  clearKeepFollowBit_Expect((Object *)&object);
  _object_free_Expect((Object *)&object);
  clearMarkBit_Expect((Object *)&object);
  
  // Call S.U.T.
  _gc_free((Object *)ptr);

  // No tests assert since it is on mocking stage
  TEST_ASSERT_EQUAL(0, object.reference);
}

void test_phase1Mark_given_reference_is_2_should_reduce_reference_to_1(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 2, .flag = 0, .free = objectAFree, .ptrA = NULL};

  ptr = &object;
  gc_free = phase1Mark;
  
  // Mocking
  setMarkBit_Expect((Object *)&object);
  clearKeepStartBit_Expect((Object *)&object);
  clearKeepFollowBit_Expect((Object *)&object);
  _object_free_Expect((Object *)&object);
  clearMarkBit_Expect((Object *)&object);
  
  // Call S.U.T.
  _gc_free((Object *)ptr);

  // No tests assert since it is on mocking stage
  TEST_ASSERT_EQUAL(1, object.reference);
}

/*
 *  ptr -> object1 (marked) ___
 *              ^              \
 *               \_____________/
 */
void test_phase1Mark_should_reduce_reference_to_0_even_though_object_is_marked(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 1, .flag = MARK, .free = objectAFree, .ptrA = NULL};
  
  ptr = &object;
  gc_free = phase1Mark;
  
  // Mocking
  // Do nothing
  
  // Call S.U.T.
  _gc_free((Object *)ptr);
  
  // No tests assert since it is on mocking stage
  TEST_ASSERT_EQUAL(0, object.reference);
}

//=================
// Test phase2Mark
//=================
void test_phase2Mark_given_an_object_reference_is_0_and_previousKeepBit_is_0_should_not_call_setKeepStartBit_or_setKeepFollowBit(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 0, .flag = 0, .free = objectAFree, .ptrA = NULL};

  ptr = &object;
  gc_free = phase2Mark;
  previousKeepBit = 0;
  
  // Mocking
  setMarkBit_Expect((Object *)&object);
  _object_free_Expect((Object *)&object);
  clearMarkBit_Expect((Object *)&object);
  
  // Call S.U.T.
  _gc_free((Object *)ptr);
  
  // No tests assert since it is on mocking stage
  TEST_ASSERT_EQUAL(0, previousKeepBit);
}

void test_phase2Mark_given_an_object_reference_is_1_and_previousKeepBit_is_0_should_call_setKeepStartBit(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 1, .flag = 0, .free = objectAFree, .ptrA = NULL};

  ptr = &object;
  gc_free = phase2Mark;
  previousKeepBit = 0;
  
  // Mocking
  setKeepStartBit_Expect((Object *)&object);
  setMarkBit_Expect((Object *)&object);
  _object_free_Expect((Object *)&object);
  clearMarkBit_Expect((Object *)&object);
  
  // Call S.U.T.
  _gc_free((Object *)ptr);
  
  // No tests assert since it is on mocking stage
  TEST_ASSERT_EQUAL(1, previousKeepBit);
}

void test_phase2Mark_given_an_object_reference_is_0_but_previousKeepBit_is_1_should_call_setKeepFollowBit(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 0, .flag = 0, .free = objectAFree, .ptrA = NULL};

  ptr = &object;
  gc_free = phase2Mark;
  previousKeepBit = 1;
  
  // Mocking
  setKeepFollowBit_Expect((Object *)&object);
  setMarkBit_Expect((Object *)&object);
  _object_free_Expect((Object *)&object);
  clearMarkBit_Expect((Object *)&object);

  // Call S.U.T.
  _gc_free((Object *)ptr);

  // No tests assert since it is on mocking stage
  TEST_ASSERT_EQUAL(1, previousKeepBit);
}

void test_phase2Mark_given_an_object_previousKeepBit_is_1_even_though_its_reference_is_1_should_call_setKeepFollowBit(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 1, .flag = 0, .free = objectAFree, .ptrA = NULL};

  ptr = &object;
  gc_free = phase2Mark;
  previousKeepBit = 1;
  
  // Mocking
  setKeepFollowBit_Expect((Object *)&object);
  setMarkBit_Expect((Object *)&object);
  _object_free_Expect((Object *)&object);
  clearMarkBit_Expect((Object *)&object);
  
  // Call S.U.T.
  _gc_free((Object *)ptr);
  
  // No tests assert since it is on mocking stage
  TEST_ASSERT_EQUAL(1, previousKeepBit);
}

//==================
// Test phase3Sweep
//==================
void test_phase3Sweep_should_free_unkept_object(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 0, .flag = 0, .free = objectAFree, .ptrA = NULL};

  ptr = &object;
  gc_free = phase3Sweep;
  previousKeepBit = 0;
  
  // Mocking
  setMarkBit_Expect((Object *)&object);
  _object_free_Expect((Object *)&object);
  clearMarkBit_Expect((Object *)&object);
  _object_free_Expect((Object *)&object);
  _free_Expect(&object);
  
  // Call S.U.T.
  _gc_free((Object *)ptr);
  
  // No tests assert since it is on mocking stage
}

void test_phase3Sweep_given_object_flag_is_KEEPSTART_should_not_free_object_and_should_increase_object_reference_by_1(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 0, .flag = KEEPSTART, .free = objectAFree, .ptrA = NULL};

  ptr = &object;
  gc_free = phase3Sweep;
  previousKeepBit = 0;
  
  // Mocking
  setMarkBit_Expect((Object *)&object);
  _object_free_Expect((Object *)&object);
  clearMarkBit_Expect((Object *)&object);
  
  // Call S.U.T.
  _gc_free((Object *)ptr);

  TEST_ASSERT_EQUAL(1, object.reference);
}

void test_phase3Sweep_object_flag_is_KEEPFOLLOW_should_not_free_object_and_should_increase_object_reference_by_1(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 0, .flag = KEEPFOLLOW, .free = objectAFree, .ptrA = NULL};

  ptr = &object;
  gc_free = phase3Sweep;
  previousKeepBit = 0;
  
  // Mocking
  setMarkBit_Expect((Object *)&object);
  _object_free_Expect((Object *)&object);
  clearMarkBit_Expect((Object *)&object);

  // Call S.U.T.
  _gc_free((Object *)ptr);
  
  TEST_ASSERT_EQUAL(1, object.reference);
}

void test_phase3Sweep_given_previousKeepBit_is_1_should_not_free_object_but_should_call_setKeepFollowBit(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 0, .flag = 0, .free = objectAFree, .ptrA = NULL};

  ptr = &object;
  gc_free = phase3Sweep;
  previousKeepBit = 1;
  
  // Mocking
  setKeepFollowBit_Expect((Object *)&object);
  setMarkBit_Expect((Object *)&object);
  _object_free_Expect((Object *)&object);
  clearMarkBit_Expect((Object *)&object);
  
  // Ignore since setKeepFollowBit is only a mock
  _object_free_Expect((Object *)&object);
  _free_Expect((Object *)&object);
  
  // Call S.U.T.
  _gc_free((Object *)ptr);
  
  // No test assert since setKeepFollowBit is only a mock
}