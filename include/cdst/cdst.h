#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "iso1366/iso1366_numeric.h"

extern bool is_dst(enum iso1366_numeric_e country, int8_t utc_offset, uint32_t time);
