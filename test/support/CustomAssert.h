#ifndef CustomAssert_H
#define CustomAssert_H

#include "Object.h"

#define TEST_ASSERT_EQUAL_Object(expectedReference, expectedFlag, actualObject) \
                    assertObject(expectedReference, expectedFlag, actualObject, __LINE__)

#endif // CustomAssert_H
