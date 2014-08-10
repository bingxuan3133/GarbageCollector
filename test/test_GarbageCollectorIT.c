#include <stdio.h>
#include <malloc.h>
#include "unity.h"
#include "CustomAssert.h"
#include "GarbageCollector.h"
#include "Flags.h"
#include "Object.h"
#include "ObjectA.h"
#include "ObjectB.h"
#include "ObjectC.h"
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

//===========
// NULL Test
//===========
void test_phase1Mark_given_NULL_should_not_have_bad_memory_access(void) {
	Object *ptr = NULL;

  gc_free = phase1Mark;
  
  // Call S.U.T.
  _gc_free((Object *)ptr);
}


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
 *  ptr -> object1 -> object2 -> object3
 *                ^      ^      /
 *                 \     |     v
 *                    object4
 */
void test_phase1Mark_case3(void) {
	Object *ptr;
  
  ObjectA *object1 = objectANew();
  ObjectA *object2 = objectANew();
  ObjectA *object3 = objectANew();
  ObjectB *object4 = objectBNew();

  ptr = objectAssign((Object *)object1);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrA = objectAssign((Object *)object3);
  object3->ptrA = objectAssign((Object *)object4);
  object4->ptrB1 = objectAssign((Object *)object2);
  object4->ptrB2 = objectAssign((Object *)object1);

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

/*
 *               ptr3 -> object3 -> object4
 *                          ^
 *                         /
 *  ptr1 -> object1 -> object2 -> object5 -> object6
 *                         \          ^
 *                          v          \
 *                       object7      ptr2
 */
void test_phase1Mark_case6(void) {
	Object *ptr1, *ptr2, *ptr3;
  
  ObjectA *object1 = objectANew();
  ObjectC *object2 = objectCNew();
  ObjectA *object3 = objectANew();
  ObjectA *object4 = objectANew();
  ObjectA *object5 = objectANew();
  ObjectA *object6 = objectANew();
  ObjectA *object7 = objectANew();

  ptr1 = objectAssign((Object *)object1);
  ptr2 = objectAssign((Object *)object5);
  ptr2 = objectAssign((Object *)object3);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrC1 = objectAssign((Object *)object3);
  object2->ptrC2 = objectAssign((Object *)object5);
  object2->ptrC3 = objectAssign((Object *)object7);
  object3->ptrA = objectAssign((Object *)object4);
  object5->ptrA = objectAssign((Object *)object6);

  gc_free = phase1Mark;
  
  // Call S.U.T.
  _gc_free((Object *)ptr1);

  // Tests
  TEST_ASSERT_EQUAL_Object(0, 0, object1);
  TEST_ASSERT_EQUAL_Object(0, 0, object2);
  TEST_ASSERT_EQUAL_Object(1, 0, object3);
  TEST_ASSERT_EQUAL_Object(0, 0, object4);
  TEST_ASSERT_EQUAL_Object(1, 0, object5);
  TEST_ASSERT_EQUAL_Object(0, 0, object6);
  TEST_ASSERT_EQUAL_Object(0, 0, object7);
  
  free(object1);
  free(object2);
  free(object3);
  free(object4);
  free(object5);
  free(object6);
  free(object7);
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
 *  ptr -> object1 -> object2 -> object3
 *                ^      ^      /
 *                 \     |     v
 *                    object4
 */
void test_phase2Mark_case3(void) {
	Object *ptr;
  
  ObjectA *object1 = objectANew();
  ObjectA *object2 = objectANew();
  ObjectA *object3 = objectANew();
  ObjectB *object4 = objectBNew();

  ptr = objectAssign((Object *)object1);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrA = objectAssign((Object *)object3);
  object3->ptrA = objectAssign((Object *)object4);
  object4->ptrB1 = objectAssign((Object *)object2);
  object4->ptrB2 = objectAssign((Object *)object1);

  previousKeepBit = 0;
  
  gc_free = phase1Mark;
  _gc_free((Object *)ptr);
  gc_free = phase2Mark;
  
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

/*
 *               ptr3 -> object3 -> object4
 *                          ^
 *                         /
 *  ptr1 -> object1 -> object2 -> object5 -> object6
 *                         \          ^
 *                          v          \
 *                       object7      ptr2
 */
void test_phase2Mark_case6(void) {
	Object *ptr1, *ptr2, *ptr3;
  
  ObjectA *object1 = objectANew();
  ObjectC *object2 = objectCNew();
  ObjectA *object3 = objectANew();
  ObjectA *object4 = objectANew();
  ObjectA *object5 = objectANew();
  ObjectA *object6 = objectANew();
  ObjectA *object7 = objectANew();

  ptr1 = objectAssign((Object *)object1);
  ptr2 = objectAssign((Object *)object5);
  ptr2 = objectAssign((Object *)object3);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrC1 = objectAssign((Object *)object3);
  object2->ptrC2 = objectAssign((Object *)object5);
  object2->ptrC3 = objectAssign((Object *)object7);
  object3->ptrA = objectAssign((Object *)object4);
  object5->ptrA = objectAssign((Object *)object6);
  
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
  TEST_ASSERT_EQUAL_Object(1, KEEPSTART, object5);
  TEST_ASSERT_EQUAL_Object(0, KEEPFOLLOW, object6);
  TEST_ASSERT_EQUAL_Object(0, 0, object7);
  
  free(object1);
  free(object2);
  free(object3);
  free(object4);
  free(object5);
  free(object6);
  free(object7);
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
 *  ptr -> object1 -> object2 -> object3
 *                ^      ^      /
 *                 \     |     v
 *                    object4
 */
void test_phase3Sweep_case3(void) {
	Object *ptr;
  
  ObjectA *object1 = objectANew();
  ObjectA *object2 = objectANew();
  ObjectA *object3 = objectANew();
  ObjectB *object4 = objectBNew();

  ptr = objectAssign((Object *)object1);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrA = objectAssign((Object *)object3);
  object3->ptrA = objectAssign((Object *)object4);
  object4->ptrB1 = objectAssign((Object *)object2);
  object4->ptrB2 = objectAssign((Object *)object1);

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
 *               ptr3 -> object3 -> object4
 *                          ^
 *                         /
 *  ptr1 -> object1 -> object2 -> object5 -> object6
 *                         \          ^
 *                          v          \
 *                       object7      ptr2
 */
void test_phase3Sweep_case6(void) {
	Object *ptr1, *ptr2, *ptr3;
  
  ObjectA *object1 = objectANew();
  ObjectC *object2 = objectCNew();
  ObjectA *object3 = objectANew();
  ObjectA *object4 = objectANew();
  ObjectA *object5 = objectANew();
  ObjectA *object6 = objectANew();
  ObjectA *object7 = objectANew();

  ptr1 = objectAssign((Object *)object1);
  ptr2 = objectAssign((Object *)object5);
  ptr2 = objectAssign((Object *)object3);
  object1->ptrA = objectAssign((Object *)object2);
  object2->ptrC1 = objectAssign((Object *)object3);
  object2->ptrC2 = objectAssign((Object *)object5);
  object2->ptrC3 = objectAssign((Object *)object7);
  object3->ptrA = objectAssign((Object *)object4);
  object5->ptrA = objectAssign((Object *)object6);

  previousKeepBit = 0;
  
  // mock free()
  _free_Expect(object7);
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
  TEST_ASSERT_EQUAL_Object(1, KEEPSTART, object5);
  TEST_ASSERT_EQUAL_Object(1, KEEPFOLLOW, object6);
  TEST_ASSERT_EQUAL_Object(0, 0, object7);
  
  free(object1);
  free(object2);
  free(object3);
  free(object4);
  free(object5);
  free(object6);
}