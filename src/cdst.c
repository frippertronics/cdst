#include <time.h>

#include "cdst/cdst.h"

#define HOUR_S (3600)

enum time_day
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
};

enum time_month
{
    JANUARY = 0, FEBRUARY, MARCH, APRIL, MAY, JUNE,
    JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
};

struct dst_transition_rules_t
{
    enum time_month begin_month;
    enum time_day begin_day;
    uint8_t begin_day_num;
    uint8_t begin_hour;
    enum time_month end_month;
    enum time_day end_day;
    uint8_t end_day_num;
    uint8_t end_hour;
    bool is_utc;
    int8_t utc_offset;
};

static inline uint8_t get_days_of_month(uint16_t year, enum time_month month)
{
    uint8_t days;
    switch (month)
    {
        case FEBRUARY:
            days = ((year % 4) == 0) ? 28 : 27;
            break;
        case JANUARY:
        case MARCH:
        case MAY:
        case JULY:
        case AUGUST:
        case OCTOBER:
        case DECEMBER:
            days = 31;
            break;
        case APRIL:
        case JUNE:
        case SEPTEMBER:
        case NOVEMBER:
            days = 30;
    }
    
    return days;
}

bool is_dst(enum iso1366_numeric_e country, int8_t utc_offset, uint32_t time)
{
    // Get DST rules
    bool is_dst = false;
    struct dst_transition_rules_t transition;
    switch(country)
    {
        case GERMANY:
            transition = (struct dst_transition_rules_t) 
            {
                .begin_month = MARCH, .begin_day = SUNDAY, .begin_day_num = 5, .begin_hour = 1,
                .end_month = OCTOBER, .end_day = SUNDAY, .end_day_num = 5, .end_hour = 1,
                .is_utc = true, utc_offset = 0,
            };
            break;
        default:
            transition = (struct dst_transition_rules_t) {0};
            break;
    }

    if (transition.is_utc == false)
    {
        if (utc_offset < 0)
        {
            time -= ((uint32_t) (0 - utc_offset)) * HOUR_S;
        }
        else
        {
            time += (uint32_t) utc_offset * HOUR_S;
        }
    }

    struct tm *p_tm;
    p_tm = gmtime((const time_t*)&time);

    enum time_day curr_dotw = p_tm->tm_wday;
    enum time_month curr_month = p_tm->tm_mon;
    uint8_t curr_hour = p_tm->tm_hour;
    uint8_t curr_dotm = p_tm->tm_mday; // Starts at 1st
    uint8_t days_of_month = get_days_of_month(p_tm->tm_year, curr_month);
    uint8_t first_dotw = ((7 + curr_dotm - 1) - curr_dotw) % 7;

    if ((curr_month < transition.begin_month) || (curr_month > transition.end_month))
    {
        is_dst = false;
    }
    else if (curr_month == transition.begin_month)
    {
        uint8_t transition_dotm = (7 * (transition.begin_day_num - 1)); // Week
        transition_dotm += (transition.begin_day < first_dotw) ? 7 - transition.begin_day - first_dotw : transition.begin_day - first_dotw;
        if (transition_dotm > days_of_month)
        {
            transition_dotm -= 7;
        } 
        if (curr_dotm < transition_dotm)
        {
            is_dst = false;
        }
        else if (curr_dotm == transition_dotm)
        {
            is_dst = (curr_hour >= transition.begin_hour);
        }
        else
        {
            is_dst = true;
        }
    }
    else if (curr_month == transition.end_month)
    {
        uint8_t transition_dotm = (7 * (transition.end_day_num - 1)); // Week
        transition_dotm += (transition.end_day < first_dotw) ? 7 - transition.end_day - first_dotw : transition.end_day - first_dotw;
        if (transition_dotm > days_of_month)
        {
            transition_dotm -= 7;
        } 

        if (curr_dotm < transition_dotm)
        {
            is_dst = true;
        }
        else if (curr_dotm == transition_dotm)
        {
            is_dst = (curr_hour < transition.end_hour);
        }
        else
        {
            is_dst = false;
        }
    }
    else
    {
        is_dst = true;
    }

    return is_dst;
}
