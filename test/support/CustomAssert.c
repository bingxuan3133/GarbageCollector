#include "unity.h"
#include "Object.h"

void assertObject(const int expectedReference,
                  const int expectedFlag,
                  const Object *actualObject,
                  const UNITY_LINE_TYPE lineNumber) {
  if(actualObject == NULL)
    UNITY_TEST_FAIL(lineNumber, "The 'actual' node is NULL");
  UNITY_TEST_ASSERT_EQUAL_INT(expectedReference, actualObject->reference, lineNumber, "The number of references is not the same");
  UNITY_TEST_ASSERT_EQUAL_INT(expectedFlag, actualObject->flag, lineNumber, "The flag is not the same");
}