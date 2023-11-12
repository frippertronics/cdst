#include <unity.h>

#include "cdst/cdst.h"

#include "iso1366_numeric.h"

#define ARR_LEN(x) (sizeof(x) / sizeof((x)[0]))

#define EU_START_2023 (1679792400)
#define EU_STOP_2023  (1698541200)
#define USA_START_2023 (1678604400)
#define USA_STOP_2023  (1699164000)
#define CUBA_START_2023 (1678597200)
#define CUBA_STOP_2023  (1699160400)
#define MOLDOVA_START_2023 (1679788800)
#define MOLDOVA_STOP_2023  (1698537600)
#define ISRAEL_START_2023 (1679616000)
#define ISRAEL_STOP_2023  (1698534000)
#define PALESTINE_START_2023 (1682726400)
#define PALESTINE_STOP_2023 (1698447600)

void setUp(void)
{

}

void tearDown(void)
{
    
}

void test_germany_2023(void)
{
    uint16_t test_country = GERMANY;
    uint32_t test_times[] = {EU_START_2023 - 1, EU_START_2023, EU_STOP_2023 - 1, EU_STOP_2023};
    bool expected[] = {false, true, true, false};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = is_dst(test_country, 0, test_times[i]);

        TEST_ASSERT(ret == expected[i]);
    }
}

void test_usa_est_2023(void)
{
    uint16_t test_country = USA;
    uint32_t test_times[] = {USA_START_2023 - 1, USA_START_2023, USA_STOP_2023 - 1, USA_STOP_2023};
    bool expected[] = {false, true, true, false};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = is_dst(test_country, -5, test_times[i]);

        TEST_ASSERT(ret == expected[i]);
    }
}

void test_cuba_2023(void)
{
    uint16_t test_country = CUBA;
    uint32_t test_times[] = {CUBA_START_2023 - 1, CUBA_START_2023, CUBA_STOP_2023 - 1, CUBA_STOP_2023};
    bool expected[] = {false, true, true, false};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = is_dst(test_country, -5, test_times[i]);

        TEST_ASSERT(ret == expected[i]);
    }
}

void test_moldova_2023(void)
{
    uint16_t test_country = MOLDOVA;
    uint32_t test_times[] = {MOLDOVA_START_2023 - 1, MOLDOVA_START_2023, MOLDOVA_STOP_2023 - 1, MOLDOVA_STOP_2023};
    bool expected[] = {false, true, true, false};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = is_dst(test_country, 2, test_times[i]);

        TEST_ASSERT(ret == expected[i]);
    }
}

void test_israel_2023(void)
{
    uint16_t test_country = ISRAEL;
    uint32_t test_times[] = {ISRAEL_START_2023 - 1, ISRAEL_START_2023, ISRAEL_STOP_2023 - 1, ISRAEL_STOP_2023};
    bool expected[] = {false, true, true, false};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = is_dst(test_country, 2, test_times[i]);

        TEST_ASSERT(ret == expected[i]);
    }
}

void test_palestine_2023(void)
{
    uint16_t test_country = PALESTINE;
    uint32_t test_times[] = {PALESTINE_START_2023 - 1, PALESTINE_START_2023, PALESTINE_STOP_2023 - 1, PALESTINE_STOP_2023};
    bool expected[] = {false, true, true, false};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = is_dst(test_country, 2, test_times[i]);

        TEST_ASSERT(ret == expected[i]);
    }
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_germany_2023);
    RUN_TEST(test_usa_est_2023);
    RUN_TEST(test_cuba_2023);
    RUN_TEST(test_moldova_2023);
    RUN_TEST(test_israel_2023);
    RUN_TEST(test_palestine_2023);

    return UNITY_END();
}