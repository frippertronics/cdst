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
#define LEBANON_START_2023 (1680127200)
#define LEBANON_STOP_2023  (1698526800)
#define EGYPT_START_2023 (1682632800)
#define EGYPT_STOP_2023  (1698354000)
#define PALESTINE_START_2023 (1682726400)
#define PALESTINE_STOP_2023 (1698447600)
#define PARAGUAY_START_2023 (1679799600)
#define PARAGUAY_STOP_2023 (1696132800)
#define CHILE_START_2023 (1680404400)
#define CHILE_STOP_2023 (1693713600)
#define AUSTRALIA_START_2023 (1680364800) // Victoria, UTC+10
#define AUSTRALIA_STOP_2023 (1696089600)  // Victoria, UTC+10
#define NEW_ZEALAND_START_2023 (1680357600)
#define NEW_ZEALAND_STOP_2023 (1695477600)

void setUp(void)
{

}

void tearDown(void)
{
    
}

void test_germany_2023(void)
{
#ifdef DISABLE_EUROPE_RULES
    TEST_IGNORE_MESSAGE("European DST rules have been disabled!");
#endif
    uint16_t test_country = GERMANY;
    uint32_t test_times[] = {EU_START_2023 - 1, EU_START_2023, EU_STOP_2023 - 1, EU_STOP_2023};
    bool expected[] = {false, true, true, false};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = cdst_is_dst(test_country, 0, test_times[i]);

        TEST_ASSERT_EQUAL(expected[i], ret);
    }
}

void test_moldova_2023(void)
{
#ifdef DISABLE_EUROPE_RULES
    TEST_IGNORE_MESSAGE("European DST rules have been disabled!");
#endif
    uint16_t test_country = MOLDOVA;
    uint32_t test_times[] = {MOLDOVA_START_2023 - 1, MOLDOVA_START_2023, MOLDOVA_STOP_2023 - 1, MOLDOVA_STOP_2023};
    bool expected[] = {false, true, true, false};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = cdst_is_dst(test_country, 2, test_times[i]);

        TEST_ASSERT_EQUAL(expected[i], ret);
    }
}

void test_usa_est_2023(void)
{
#ifdef DISABLE_AMERICA_RULES
    TEST_IGNORE_MESSAGE("American DST rules have been disabled!");
#endif
    uint16_t test_country = USA;
    uint32_t test_times[] = {USA_START_2023 - 1, USA_START_2023, USA_STOP_2023 - 1, USA_STOP_2023};
    bool expected[] = {false, true, true, false};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = cdst_is_dst(test_country, -5, test_times[i]);

        TEST_ASSERT_EQUAL(expected[i], ret);
    }
}

void test_cuba_2023(void)
{
#ifdef DISABLE_AMERICA_RULES
    TEST_IGNORE_MESSAGE("American DST rules have been disabled!");
#endif
    uint16_t test_country = CUBA;
    uint32_t test_times[] = {CUBA_START_2023 - 1, CUBA_START_2023, CUBA_STOP_2023 - 1, CUBA_STOP_2023};
    bool expected[] = {false, true, true, false};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = cdst_is_dst(test_country, -5, test_times[i]);

        TEST_ASSERT_EQUAL(expected[i], ret);
    }
}

void test_paraguay_2023(void)
{
#ifdef DISABLE_AMERICA_RULES
    TEST_IGNORE_MESSAGE("American DST rules have been disabled!");
#endif
    uint16_t test_country = PARAGUAY;
    uint32_t test_times[] = {PARAGUAY_START_2023 - 1, PARAGUAY_START_2023, PARAGUAY_STOP_2023 - 1, PARAGUAY_STOP_2023};
    bool expected[] = {true, false, false, true};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = cdst_is_dst(test_country, -4, test_times[i]);

        TEST_ASSERT_EQUAL(expected[i], ret);
    }
}

void test_chile_2023(void)
{
#ifdef DISABLE_AMERICA_RULES
    TEST_IGNORE_MESSAGE("American DST rules have been disabled!");
#endif
    uint16_t test_country = CHILE;
    uint32_t test_times[] = {CHILE_START_2023 - 1, CHILE_START_2023, CHILE_STOP_2023 - 1, CHILE_STOP_2023};
    bool expected[] = {true, false, false, true};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = cdst_is_dst(test_country, -4, test_times[i]);

        TEST_ASSERT_EQUAL(expected[i], ret);
    }
}

void test_israel_2023(void)
{
#ifdef DISABLE_ASIA_RULES
    TEST_IGNORE_MESSAGE("Asian DST rules have been disabled!");
#endif
    uint16_t test_country = ISRAEL;
    uint32_t test_times[] = {ISRAEL_START_2023 - 1, ISRAEL_START_2023, ISRAEL_STOP_2023 - 1, ISRAEL_STOP_2023};
    bool expected[] = {false, true, true, false};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = cdst_is_dst(test_country, 2, test_times[i]);

        TEST_ASSERT_EQUAL(expected[i], ret);
    }
}

void test_lebanon_2023(void)
{
#ifdef DISABLE_ASIA_RULES
    TEST_IGNORE_MESSAGE("Asian DST rules have been disabled!");
#endif
    uint16_t test_country = LEBANON;
    uint32_t test_times[] = {LEBANON_START_2023 - 1, LEBANON_START_2023, LEBANON_STOP_2023 - 1, LEBANON_STOP_2023};
    bool expected[] = {false, true, true, false};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = cdst_is_dst(test_country, 2, test_times[i]);

        TEST_ASSERT_EQUAL(expected[i], ret);
    }
}

void test_palestine_2023(void)
{
#ifdef DISABLE_ASIA_RULES
    TEST_IGNORE_MESSAGE("Asian DST rules have been disabled!");
#endif
    uint16_t test_country = PALESTINE;
    uint32_t test_times[] = {PALESTINE_START_2023 - 1, PALESTINE_START_2023, PALESTINE_STOP_2023 - 1, PALESTINE_STOP_2023};
    bool expected[] = {false, true, true, false};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = cdst_is_dst(test_country, 2, test_times[i]);

        TEST_ASSERT_EQUAL(expected[i], ret);
    }
}

void test_egypt_2023(void)
{
#ifdef DISABLE_AFRICA_RULES
    TEST_IGNORE_MESSAGE("African DST rules have been disabled!");
#endif
    uint16_t test_country = EGYPT;
    uint32_t test_times[] = {EGYPT_START_2023 - 1, EGYPT_START_2023, EGYPT_STOP_2023 - 1, EGYPT_STOP_2023};
    bool expected[] = {false, true, true, false};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = cdst_is_dst(test_country, 2, test_times[i]);

        TEST_ASSERT_EQUAL(expected[i], ret);
    }
}

void test_australia_2023(void)
{
#ifdef DISABLE_OCEANIA_RULES
    TEST_IGNORE_MESSAGE("Oceanian DST rules have been disabled!");
#endif
    uint16_t test_country = AUSTRALIA;
    uint32_t test_times[] = {AUSTRALIA_START_2023 - 1, AUSTRALIA_START_2023, AUSTRALIA_STOP_2023 - 1, AUSTRALIA_STOP_2023};
    bool expected[] = {true, false, false, true};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = cdst_is_dst(test_country, 10, test_times[i]);

        TEST_ASSERT_EQUAL(expected[i], ret);
    }
}

void test_new_zealand_2023(void)
{
#ifdef DISABLE_OCEANIA_RULES
    TEST_IGNORE_MESSAGE("Oceanian DST rules have been disabled!");
#endif
    uint16_t test_country = NEW_ZEALAND;
    uint32_t test_times[] = {NEW_ZEALAND_START_2023 - 1, NEW_ZEALAND_START_2023, NEW_ZEALAND_STOP_2023 - 1, NEW_ZEALAND_STOP_2023};
    bool expected[] = {true, false, false, true};

    for(int i = 0; i < ARR_LEN(test_times); i++)
    {
        bool ret = cdst_is_dst(test_country, 12, test_times[i]);

        TEST_ASSERT_EQUAL(expected[i], ret);
    }
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_usa_est_2023);
    RUN_TEST(test_cuba_2023);
    RUN_TEST(test_germany_2023);
    RUN_TEST(test_moldova_2023);
    RUN_TEST(test_israel_2023);
    RUN_TEST(test_lebanon_2023);
    RUN_TEST(test_egypt_2023);
    RUN_TEST(test_palestine_2023);
    RUN_TEST(test_paraguay_2023);
    RUN_TEST(test_chile_2023);
    RUN_TEST(test_australia_2023);
    RUN_TEST(test_new_zealand_2023);

    return UNITY_END();
}