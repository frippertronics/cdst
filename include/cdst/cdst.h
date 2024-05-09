#pragma once

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Check if daylight savings time is active in the given country at the given epoch
 * 
 * The base UTC-offset is used to account for local time-zone differences in countries with
 * multiple time zones.
 * 
 * @param iso1366_country_numeric_id ISO1366 Country ID 
 * @param base_utc_offset UTC-offset when DST is not active
 * @param curr_epoch_time Current epoch time (aka UNIX time)
 * @return true if DST is active
 * @return false if DST is not active
 */
extern bool cdst_is_dst(uint16_t iso1366_country_numeric_id, int8_t base_utc_offset, uint32_t curr_epoch_time);
