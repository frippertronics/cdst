#include <time.h>

#include "cdst/cdst.h"

#include "iso1366_numeric.h"

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
    enum time_month end_month;
    enum time_day end_day;
    uint8_t begin_day_num;
    uint8_t begin_hour;
    uint8_t end_day_num;
    uint8_t end_hour;
    bool is_local;
};

#define TRANSITION_RULE(b_month,b_day,b_daynum,b_hour,e_month,e_day,e_daynum,e_hour,local) \
    (struct dst_transition_rules_t) \
    { \
        .begin_month = (b_month), .begin_day = (b_day), .begin_day_num = (b_daynum), .begin_hour = (b_hour), \
        .end_month = (e_month), .end_day = (e_day), .end_day_num = (e_daynum), .end_hour = (e_hour), \
        .is_local = (local) \
    }

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

bool is_dst(uint16_t iso1366_country_numeric_id, int8_t base_utc_offset, uint32_t curr_epoch_time)
{
    // Get DST rules
    bool is_dst = false;
    struct dst_transition_rules_t transition;
    switch((enum iso1366_numeric_e) iso1366_country_numeric_id)
    {
        case GERMANY:
            transition = TRANSITION_RULE(MARCH, SUNDAY, 5, 1, OCTOBER, SUNDAY, 5, 1, false);
            break;
        case USA:
            transition = TRANSITION_RULE(MARCH, SUNDAY, 2, 2, NOVEMBER, SUNDAY, 1, 2, true);
            break;
        case CUBA:
            transition = TRANSITION_RULE(MARCH, SUNDAY, 2, 0, NOVEMBER, SUNDAY, 1, 1, true);
            break;
        default:
            transition = (struct dst_transition_rules_t) {0};
            break;
    }

    if (transition.is_local)
    {
        if (base_utc_offset < 0)
        {
            curr_epoch_time -= ((uint32_t) (0 - base_utc_offset)) * HOUR_S;
        }
        else
        {
            curr_epoch_time += (uint32_t) base_utc_offset * HOUR_S;
        }
    }

    struct tm *p_tm;
    time_t curr_time = (time_t) curr_epoch_time;
    p_tm = gmtime((const time_t*) &curr_time);

    enum time_day curr_dotw = p_tm->tm_wday;
    enum time_month curr_month = p_tm->tm_mon;
    uint8_t curr_hour = p_tm->tm_hour;
    uint8_t curr_dotm = p_tm->tm_mday; // Starts at 1st
    uint8_t days_of_month = get_days_of_month(p_tm->tm_year, curr_month);
    uint8_t first_dotw = (curr_dotw + 7 - ((curr_dotm - 1) % 7)) % 7;

    if ((curr_month < transition.begin_month) || (curr_month > transition.end_month))
    {
        is_dst = false;
    }
    else if (curr_month == transition.begin_month)
    {
        uint8_t transition_dotm = (7 * (transition.begin_day_num - 1)) + 1; // Week offset + DOTM starts at 1
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
        uint8_t transition_dotm = (7 * (transition.end_day_num - 1)) + 1; // Week offset + DOTM starts at 1
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
            if (transition.is_local)
            {
                // The current time is offset by 1 hour due to DST. On transition, the can be both DST and not.
                is_dst = (((curr_hour + 1) < transition.end_hour) && (curr_hour < transition.end_hour));
            }
            else
            {
                is_dst = (curr_hour < transition.end_hour);
            }
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
