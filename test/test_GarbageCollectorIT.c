#include <stdio.h>
#include <malloc.h>
#include "unity.h"
#include "CustomAssert.h"
#include "GarbageCollector.h"
#include "Flags.h"
#include "Object.h"
#include "ObjectA.h"
#include "gc_free.h"
#include "object_free.h"
#include "mock_free.h"

void setUp(void)
{
}

void tearDown(void)
{
}

//==================
// Integration Test
//==================

//=================
// Test phase1Mark
//=================
/*
 *  ptr -> object1 -> object2 -> object3
 *                        ^       /
 *                         \     v
 *                         object4
 */
void test_phase1Mark_case1(void) {
	Object *ptr;
  
  ObjectA *object1 = objectANew();
  ObjectA *object2 = objectANew();
  ObjectA *object3 = objectANew();
  ObjectA *object4 = objectANew();

  ptr = objectAssign((Object *)object1);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrA = objectAssign((Object *)object3);
  object3->ptrA = objectAssign((Object *)object4);
  object4->ptrA = objectAssign((Object *)object2);

  gc_free = phase1Mark;
  
  // Call S.U.T.
  _gc_free((Object *)ptr);

  // Tests
  TEST_ASSERT_EQUAL_Object(0, 0, object1);
  TEST_ASSERT_EQUAL_Object(0, 0, object2);
  TEST_ASSERT_EQUAL_Object(0, 0, object3);
  TEST_ASSERT_EQUAL_Object(0, 0, object4);

  free(object1);
  free(object2);
  free(object3);
  free(object4);
}

/*
 *  ptr1 -> object1 -> object2 -> object3 -> object4
 *                                  ^
 *                                 /
 *                              ptr2
 */
void test_phase1Mark_case2(void) {
	Object *ptr1, *ptr2;
  
  ObjectA *object1 = objectANew();
  ObjectA *object2 = objectANew();
  ObjectA *object3 = objectANew();
  ObjectA *object4 = objectANew();

  ptr1 = objectAssign((Object *)object1);
  ptr2 = objectAssign((Object *)object3);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrA = objectAssign((Object *)object3);
  object3->ptrA = objectAssign((Object *)object4);

  gc_free = phase1Mark;

  // Call S.U.T.
  _gc_free((Object *)ptr1);

  // Tests
  TEST_ASSERT_EQUAL_Object(0, 0, object1);
  TEST_ASSERT_EQUAL_Object(0, 0, object2);
  TEST_ASSERT_EQUAL_Object(1, 0, object3);
  TEST_ASSERT_EQUAL_Object(0, 0, object4);

  free(object1);
  free(object2);
  free(object3);
  free(object4);
}

/*
 *                                 ptr2
 *                                  |
 *                                  v
 *  ptr1 -> object1 -> object2 -> object3
 *                      ^              |
 *                      |              v  
 *                     object5 <- object4
 */
void test_phase1Mark_case4(void) {
	Object *ptr1, *ptr2;
  
  ObjectA *object1 = objectANew();
  ObjectA *object2 = objectANew();
  ObjectA *object3 = objectANew();
  ObjectA *object4 = objectANew();
  ObjectA *object5 = objectANew();

  ptr1 = objectAssign((Object *)object1);
  ptr2 = objectAssign((Object *)object3);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrA = objectAssign((Object *)object3);
  object3->ptrA = objectAssign((Object *)object4);
  object4->ptrA = objectAssign((Object *)object5);
  object5->ptrA = objectAssign((Object *)object2);

  gc_free = phase1Mark;
  
  // Call S.U.T.
  _gc_free((Object *)ptr1);

  // Tests
  TEST_ASSERT_EQUAL_Object(0, 0, object1);
  TEST_ASSERT_EQUAL_Object(0, 0, object2);
  TEST_ASSERT_EQUAL_Object(1, 0, object3);
  TEST_ASSERT_EQUAL_Object(0, 0, object4);
  TEST_ASSERT_EQUAL_Object(0, 0, object5);

  free(object1);
  free(object2);
  free(object3);
  free(object4);
  free(object5);
}

/*
 *                                             ptr2
 *                                              |
 *                                              v
 *  ptr1 -> object1 -> object2 -> object3 -> object4
 *                          ^                / 
 *                           \              v
 *                          object6 <- object5
 */
void test_phase1Mark_case5(void) {
	Object *ptr1, *ptr2;
  
  ObjectA *object1 = objectANew();
  ObjectA *object2 = objectANew();
  ObjectA *object3 = objectANew();
  ObjectA *object4 = objectANew();
  ObjectA *object5 = objectANew();
  ObjectA *object6 = objectANew();

  ptr1 = objectAssign((Object *)object1);
  ptr2 = objectAssign((Object *)object4);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrA = objectAssign((Object *)object3);
  object3->ptrA = objectAssign((Object *)object4);
  object4->ptrA = objectAssign((Object *)object5);
  object5->ptrA = objectAssign((Object *)object6);
  object6->ptrA = objectAssign((Object *)object2);

  gc_free = phase1Mark;
  
  // Call S.U.T.
  _gc_free((Object *)ptr1);

  // Tests
  TEST_ASSERT_EQUAL_Object(0, 0, object1);
  TEST_ASSERT_EQUAL_Object(0, 0, object2);
  TEST_ASSERT_EQUAL_Object(0, 0, object3);
  TEST_ASSERT_EQUAL_Object(1, 0, object4);
  TEST_ASSERT_EQUAL_Object(0, 0, object5);
  TEST_ASSERT_EQUAL_Object(0, 0, object6);
  
  free(object1);
  free(object2);
  free(object3);
  free(object4);
  free(object5);
  free(object6);
}

//=================
// Test phase2Mark
//=================
/*
 *  ptr -> object1 -> object2 -> object3
 *                        ^       /
 *                         \     v
 *                         object4
 */
void test_phase2Mark_case1(void) {
	Object *ptr;
  
  ObjectA *object1 = objectANew();
  ObjectA *object2 = objectANew();
  ObjectA *object3 = objectANew();
  ObjectA *object4 = objectANew();

  ptr = objectAssign((Object *)object1);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrA = objectAssign((Object *)object3);
  object3->ptrA = objectAssign((Object *)object4);
  object4->ptrA = objectAssign((Object *)object2);

  gc_free = phase1Mark;
  _gc_free((Object *)ptr);
  gc_free = phase2Mark;
  
  // Call S.U.T.
  _gc_free((Object *)ptr);

  // Tests
  // TEST_ASSERT_EQUAL_Object(0, 0, object1);
  // TEST_ASSERT_EQUAL_Object(0, 0, object2);
  // TEST_ASSERT_EQUAL_Object(0, 0, object3);
  // TEST_ASSERT_EQUAL_Object(0, 0, object4);

  // free(object1);
  // free(object2);
  // free(object3);
  // free(object4);
}

/*
 *  ptr1 -> object1 -> object2 -> object3 -> object4
 *                                  ^
 *                                 /
 *                              ptr2
 */
void test_phase2Mark_case2(void) {
	Object *ptr1, *ptr2;
  
  ObjectA *object1 = objectANew();
  ObjectA *object2 = objectANew();
  ObjectA *object3 = objectANew();
  ObjectA *object4 = objectANew();

  ptr1 = objectAssign((Object *)object1);
  ptr2 = objectAssign((Object *)object3);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrA = objectAssign((Object *)object3);
  object3->ptrA = objectAssign((Object *)object4);
  
  previousKeepBit = 0;
  
  gc_free = phase1Mark;
  _gc_free((Object *)ptr1);
  gc_free = phase2Mark;
  
  // Call S.U.T.
  _gc_free((Object *)ptr1);

  // Tests
  TEST_ASSERT_EQUAL_Object(0, 0, object1);
  TEST_ASSERT_EQUAL_Object(0, 0, object2);
  TEST_ASSERT_EQUAL_Object(1, KEEPSTART, object3);
  TEST_ASSERT_EQUAL_Object(0, KEEPFOLLOW, object4);
  TEST_ASSERT_EQUAL(0, previousKeepBit);

  free(object1);
  free(object2);
  free(object3);
  free(object4);
}

/*
 *                                 ptr2
 *                                  |
 *                                  v
 *  ptr1 -> object1 -> object2 -> object3
 *                      ^              |
 *                      |              v  
 *                     object5 <- object4
 */
void test_phase2Mark_case4(void) {
	Object *ptr1, *ptr2;
  
  ObjectA *object1 = objectANew();
  ObjectA *object2 = objectANew();
  ObjectA *object3 = objectANew();
  ObjectA *object4 = objectANew();
  ObjectA *object5 = objectANew();

  ptr1 = objectAssign((Object *)object1);
  ptr2 = objectAssign((Object *)object3);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrA = objectAssign((Object *)object3);
  object3->ptrA = objectAssign((Object *)object4);
  object4->ptrA = objectAssign((Object *)object5);
  object5->ptrA = objectAssign((Object *)object2);
  
  previousKeepBit = 0;
  
  gc_free = phase1Mark;
  _gc_free((Object *)ptr1);
  gc_free = phase2Mark;
  
  // Call S.U.T.
  _gc_free((Object *)ptr1);

  // Tests
  TEST_ASSERT_EQUAL_Object(0, 0, object1);
  TEST_ASSERT_EQUAL_Object(0, KEEPFOLLOW, object2);
  TEST_ASSERT_EQUAL_Object(1, KEEPSTART, object3);
  TEST_ASSERT_EQUAL_Object(0, KEEPFOLLOW, object4);
  TEST_ASSERT_EQUAL_Object(0, KEEPFOLLOW, object5);

  free(object1);
  free(object2);
  free(object3);
  free(object4);
  free(object5);
}

/*
 *                                             ptr2
 *                                              |
 *                                              v
 *  ptr1 -> object1 -> object2 -> object3 -> object4
 *                          ^                / 
 *                           \              v
 *                          object6 <- object5
 */
void test_phase2Mark_case5(void) {
	Object *ptr1, *ptr2;
  
  ObjectA *object1 = objectANew();
  ObjectA *object2 = objectANew();
  ObjectA *object3 = objectANew();
  ObjectA *object4 = objectANew();
  ObjectA *object5 = objectANew();
  ObjectA *object6 = objectANew();

  ptr1 = objectAssign((Object *)object1);
  ptr2 = objectAssign((Object *)object4);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrA = objectAssign((Object *)object3);
  object3->ptrA = objectAssign((Object *)object4);
  object4->ptrA = objectAssign((Object *)object5);
  object5->ptrA = objectAssign((Object *)object6);
  object6->ptrA = objectAssign((Object *)object2);

  previousKeepBit = 0;
  
  gc_free = phase1Mark;
  _gc_free((Object *)ptr1);
  gc_free = phase2Mark;
  
  // Call S.U.T.
  _gc_free((Object *)ptr1);

  // Tests
  TEST_ASSERT_EQUAL_Object(0, 0, object1);
  TEST_ASSERT_EQUAL_Object(0, KEEPFOLLOW, object2);
  TEST_ASSERT_EQUAL_Object(0, 0, object3);
  TEST_ASSERT_EQUAL_Object(1, KEEPSTART, object4);
  TEST_ASSERT_EQUAL_Object(0, KEEPFOLLOW, object5);
  TEST_ASSERT_EQUAL_Object(0, KEEPFOLLOW, object6);
  
  free(object1);
  free(object2);
  free(object3);
  free(object4);
  free(object5);
  free(object6);
}

//=================
// Test phase3Sweep
//=================
/*
 *  ptr -> object1 -> object2 -> object3
 *                        ^       /
 *                         \     v
 *                         object4
 */
void test_phase3Sweep_case1(void) {
	Object *ptr;
  
  ObjectA *object1 = objectANew();
  ObjectA *object2 = objectANew();
  ObjectA *object3 = objectANew();
  ObjectA *object4 = objectANew();

  ptr = objectAssign((Object *)object1);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrA = objectAssign((Object *)object3);
  object3->ptrA = objectAssign((Object *)object4);
  object4->ptrA = objectAssign((Object *)object2);
  
  previousKeepBit = 0;
  
  // mock free()
  _free_Expect(object4);
  _free_Expect(object3);
  _free_Expect(object2);
  _free_Expect(object1);
  
  gc_free = phase1Mark;
  _gc_free((Object *)ptr);
  gc_free = phase2Mark;
  _gc_free((Object *)ptr);
  gc_free = phase3Sweep;

  // Call S.U.T.
  _gc_free((Object *)ptr);

  // Tests
  TEST_ASSERT_EQUAL_Object(0, 0, object1);
  TEST_ASSERT_EQUAL_Object(0, 0, object2);
  TEST_ASSERT_EQUAL_Object(0, 0, object3);
  TEST_ASSERT_EQUAL_Object(0, 0, object4);

  free(object1);
  free(object2);
  free(object3);
  free(object4);
}

/*
 *  ptr1 -> object1 -> object2 -> object3 -> object4
 *                                  ^
 *                                 /
 *                              ptr2
 */
void test_phase3Sweep_case2(void) {
	Object *ptr1, *ptr2;
  
  ObjectA *object1 = objectANew();
  ObjectA *object2 = objectANew();
  ObjectA *object3 = objectANew();
  ObjectA *object4 = objectANew();

  ptr1 = objectAssign((Object *)object1);
  ptr2 = objectAssign((Object *)object3);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrA = objectAssign((Object *)object3);
  object3->ptrA = objectAssign((Object *)object4);
  
  previousKeepBit = 0;
  
  // mock free()
  _free_Expect(object2);
  _free_Expect(object1);
  
  gc_free = phase1Mark;
  _gc_free((Object *)ptr1);
  gc_free = phase2Mark;
  _gc_free((Object *)ptr1);
  gc_free = phase3Sweep;
  
  // Call S.U.T.
  _gc_free((Object *)ptr1);

  // Tests
  TEST_ASSERT_EQUAL_Object(0, 0, object1);
  TEST_ASSERT_EQUAL_Object(0, 0, object2);
  TEST_ASSERT_EQUAL_Object(1, KEEPSTART, object3);
  TEST_ASSERT_EQUAL_Object(1, KEEPFOLLOW, object4);
  TEST_ASSERT_EQUAL(0, previousKeepBit);

  free(object1);
  free(object2);
  free(object3);
  free(object4);
}


/*
 *                                 ptr2
 *                                  |
 *                                  v
 *  ptr1 -> object1 -> object2 -> object3
 *                      ^              |
 *                      |              v  
 *                     object5 <- object4
 */
void test_phase3Sweep_case4(void) {
	Object *ptr1, *ptr2;
  
  ObjectA *object1 = objectANew();
  ObjectA *object2 = objectANew();
  ObjectA *object3 = objectANew();
  ObjectA *object4 = objectANew();
  ObjectA *object5 = objectANew();

  ptr1 = objectAssign((Object *)object1);
  ptr2 = objectAssign((Object *)object3);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrA = objectAssign((Object *)object3);
  object3->ptrA = objectAssign((Object *)object4);
  object4->ptrA = objectAssign((Object *)object5);
  object5->ptrA = objectAssign((Object *)object2);

  previousKeepBit = 0;
  
  // mock free()
  _free_Expect(object1);
  
  gc_free = phase1Mark;
  _gc_free((Object *)ptr1);
  gc_free = phase2Mark;
  _gc_free((Object *)ptr1);
  gc_free = phase3Sweep;
  
  // Call S.U.T.
  _gc_free((Object *)ptr1);
  
  // Tests
  TEST_ASSERT_EQUAL_Object(0, 0, object1);
  TEST_ASSERT_EQUAL_Object(1, KEEPFOLLOW, object2);
  TEST_ASSERT_EQUAL_Object(2, KEEPSTART, object3);
  TEST_ASSERT_EQUAL_Object(1, KEEPFOLLOW, object4);
  TEST_ASSERT_EQUAL_Object(1, KEEPFOLLOW, object5);

  free(object1);
  free(object2);
  free(object3);
  free(object4);
  free(object5);
}

/*
 *                                             ptr2
 *                                              |
 *                                              v
 *  ptr1 -> object1 -> object2 -> object3 -> object4
 *                          ^                / 
 *                           \              v
 *                          object6 <- object5
 */
void test_phase3Sweep_case5(void) {
	Object *ptr1, *ptr2;
  
  ObjectA *object1 = objectANew();
  ObjectA *object2 = objectANew();
  ObjectA *object3 = objectANew();
  ObjectA *object4 = objectANew();
  ObjectA *object5 = objectANew();
  ObjectA *object6 = objectANew();

  ptr1 = objectAssign((Object *)object1);
  ptr2 = objectAssign((Object *)object4);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrA = objectAssign((Object *)object3);
  object3->ptrA = objectAssign((Object *)object4);
  object4->ptrA = objectAssign((Object *)object5);
  object5->ptrA = objectAssign((Object *)object6);
  object6->ptrA = objectAssign((Object *)object2);

  previousKeepBit = 0;
  
  // mock free()
  _free_Expect(object1);
  
  gc_free = phase1Mark;
  _gc_free((Object *)ptr1);
  gc_free = phase2Mark;
  _gc_free((Object *)ptr1);
  gc_free = phase3Sweep;
  
  // Call S.U.T.
  _gc_free((Object *)ptr1);

  // Tests
  TEST_ASSERT_EQUAL_Object(0, 0, object1);
  TEST_ASSERT_EQUAL_Object(1, KEEPFOLLOW, object2);
  TEST_ASSERT_EQUAL_Object(1, KEEPFOLLOW, object3);
  TEST_ASSERT_EQUAL_Object(2, KEEPSTART, object4);
  TEST_ASSERT_EQUAL_Object(1, KEEPFOLLOW, object5);
  TEST_ASSERT_EQUAL_Object(1, KEEPFOLLOW, object6);
  
  free(object1);
  free(object2);
  free(object3);
  free(object4);
  free(object5);
  free(object6);
}

/*



void test_phase1Mark_should_do_nothing_if_object1_is_marked(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 1, .flag = MARK, .free = objectAFree, .ptrA = NULL};
  
  ptr = &object;
  gc_free = phase1Mark;
  
  // Mocking
  // Do nothing
  
  // Call S.U.T.
  _gc_free((Object *)ptr);
  
  // No tests assert since it is on mocking stage
}

//=================
// Test phase2Mark
//=================
void test_phase2Mark(void) {
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
}

void test_phase2Mark_should_keep_object_if_its_reference_is_not_reduced_zero(void) {
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
}

void test_phase2Mark_should_setKeepFollowBit_object_if_previous_object_KEEP_flag_is_1(void) {
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
}

void test_phase2Mark_should_set_previousKeepBit_to_0_when_returning_from_KEEPSTART_object(void) {
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
  TEST_ASSERT_EQUAL(0, previousKeepBit);
}

//==================
// Test phase3Sweep
//==================
void test_phase3Sweep_should_sweep_unkept_object(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 0, .flag = 0, .free = objectAFree, .ptrA = NULL};

  ptr = &object;
  gc_free = phase3Sweep;
  previousKeepBit = 0;
  
  // Mocking
  setMarkBit_Expect((Object *)&object);
  _object_free_Expect((Object *)&object);
  clearMarkBit_Expect((Object *)&object);
  _free_Expect(&object);
  
  // Call S.U.T.
  _gc_free((Object *)ptr);
  
  // No tests assert since it is on mocking stage
}

void test_phase3Sweep_should_not_sweep_KEEPSTART_object_and_add_1_on_its_reference(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 0, .flag = KEEPSTART, .free = objectAFree, .ptrA = NULL};

  ptr = &object;
  gc_free = phase3Sweep;
  previousKeepBit = 0;
  
  // Mocking
  setMarkBit_Expect((Object *)&object);
  _object_free_Expect((Object *)&object);
  clearMarkBit_Expect((Object *)&object);
  clearKeepStartBit_Expect((Object *)&object);
  
  // Call S.U.T.
  _gc_free((Object *)ptr);

  TEST_ASSERT_EQUAL(1, object.reference);
}

void test_phase3Sweep_should_not_sweep_KEEPFOLLOW_object_and_add_1_on_its_reference(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 0, .flag = KEEPFOLLOW, .free = objectAFree, .ptrA = NULL};

  ptr = &object;
  gc_free = phase3Sweep;
  previousKeepBit = 0;
  
  // Mocking
  setMarkBit_Expect((Object *)&object);
  _object_free_Expect((Object *)&object);
  clearMarkBit_Expect((Object *)&object);
  clearKeepFollowBit_Expect((Object *)&object);
  
  // Call S.U.T.
  _gc_free((Object *)ptr);
  
  TEST_ASSERT_EQUAL(1, object.reference);
}

void test_phase3Sweep_should_not_sweep_object_if_previousKeepBit_is_1(void) {
	ObjectA *ptr;
  ObjectA object = {.reference = 0, .flag = KEEPSTART, .free = objectAFree, .ptrA = NULL};

  ptr = &object;
  gc_free = phase3Sweep;
  previousKeepBit = 1;
  
  // Mocking
  setMarkBit_Expect((Object *)&object);
  _object_free_Expect((Object *)&object);
  clearMarkBit_Expect((Object *)&object);
  clearKeepStartBit_Expect((Object *)&object);
  
  // Call S.U.T.
  _gc_free((Object *)ptr);

  TEST_ASSERT_EQUAL(1, object.reference);
}



*/
