#include <unity.h>

#include "cdst/cdst.h"

void setUp(void)
{

}

void tearDown(void)
{
    
}


void test_sanity(void)
{
    TEST_ASSERT_TRUE(false);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_sanity);

    return UNITY_END();
}