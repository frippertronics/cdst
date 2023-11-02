#pragma once

#include <stdbool.h>
#include <stdint.h>

extern bool is_dst(uint16_t iso1366_country_numeric_id, int8_t base_utc_offset, uint32_t curr_epoch_time);
