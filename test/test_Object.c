#include "unity.h"
#include "CustomAssert.h"
#include "Object.h"
#include "GarbageCollector.h"
#include "Flags.h"
#include "gc_free.h"
#include "object_free.h"
#include "free.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_objectDump(void) {
  Object obj = {.reference = 0, .flag = 0};
  objectDump(&obj);
  obj.flag |= MARK;
  objectDump(&obj);
  obj.flag |= KEEPSTART;
  objectDump(&obj);
}

void test_objectAssign(void) {
  Object obj = {.reference = 0, .flag = 0};
  Object *ptr;
  
  ptr = objectAssign(&obj);  
  
  TEST_ASSERT_EQUAL_Object(1, 0, ptr);
}