#include "unity.h"
#include "Object.h"
#include "GarbageCollector.h"
#include "Flags.h"
#include "object_free.h"
#include "free.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_dumpObject(void) {
  Object obj = {.reference = 0, .flag = 0};
  dumpObject(&obj);
  obj.flag |= MARK;
  dumpObject(&obj);
  obj.flag |= KEEPSTART;
  dumpObject(&obj);
}

void test_objectAssign(void) {

}