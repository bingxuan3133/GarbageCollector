#include "unity.h"
#include "Flags.h"
#include "free.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_setMarkBit_should_set_an_object_MARK_flag_to_1() {
  Object object = {.reference = 0, .flag = 0};
  
  setMarkBit(&object);
  
  TEST_ASSERT_EQUAL(1, getMarkBit(&object));
  TEST_ASSERT_EQUAL(0, getKeepStartBit(&object));
  TEST_ASSERT_EQUAL(0, getKeepFollowBit(&object));
}

void test_clearMarkBit_should_clear_an_object_MARK_flag_to_0() {
  Object object = {.reference = 0, .flag = MARK};
  
  clearMarkBit(&object);
  
  TEST_ASSERT_EQUAL(0, getMarkBit(&object));
  TEST_ASSERT_EQUAL(0, getKeepStartBit(&object));
  TEST_ASSERT_EQUAL(0, getKeepFollowBit(&object));
}

void test_setKeepStartBit_should_set_an_object_KEEPSTART_flag_to_1() {
  Object object = {.reference = 0, .flag = 0};
  
  setKeepStartBit(&object);
  
  TEST_ASSERT_EQUAL(0, getMarkBit(&object));
  TEST_ASSERT_EQUAL(1, getKeepStartBit(&object));
  TEST_ASSERT_EQUAL(0, getKeepFollowBit(&object));
}

void test_clearKeepStartBit_should_clear_an_object_KEEPSTART_flag_to_0() {
  Object object = {.reference = 0, .flag = KEEPSTART};
  
  clearKeepStartBit(&object);
  
  TEST_ASSERT_EQUAL(0, getMarkBit(&object));
  TEST_ASSERT_EQUAL(0, getKeepStartBit(&object));
  TEST_ASSERT_EQUAL(0, getKeepFollowBit(&object));
}

void test_setKeepStartBit_should_set_an_object_KEEPFOLLOW_flag_to_1() {
  Object object = {.reference = 0, .flag = 0};
  
  setKeepFollowBit(&object);
  
  TEST_ASSERT_EQUAL(0, getMarkBit(&object));
  TEST_ASSERT_EQUAL(0, getKeepStartBit(&object));
  TEST_ASSERT_EQUAL(1, getKeepFollowBit(&object));
}

void test_clearKeepStartBit_should_clear_an_object_KEEPFOLLOW_flag_to_0() {
  Object object = {.reference = 0, .flag = KEEPFOLLOW};
  
  clearKeepFollowBit(&object);
  
  TEST_ASSERT_EQUAL(0, getMarkBit(&object));
  TEST_ASSERT_EQUAL(0, getKeepStartBit(&object));
  TEST_ASSERT_EQUAL(0, getKeepFollowBit(&object));
}

