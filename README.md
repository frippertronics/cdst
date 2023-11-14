# CDST - A DST libary in C

This repository provides a DST library for C-based projects which require
Daylight Saving Time functionality.

The library is based on current DST transitions as described by [Wikipedia](https://en.wikipedia.org/wiki/Daylight_saving_time_by_country).

As DST is a binary state, the library features one function that checks if the current time, expressed as
32-bit unsigned UNIX time, is within the specified country's DST window. The window is stored as part of the
library and is referenced by the country's [ISO 3166-1 numeric](https://en.wikipedia.org/wiki/ISO_3166-1_numeric) code.

# Requirements

- GCC
- CMake
- Ruby (testing only)

## Test timestamp generation

Test timestamps for each country's transitions was generated using the following Python sequence:

```python
import pytz, datetime

tz = "Europe/Berlin"
num_entries = 30

for dt in pytz.timezone(tz)._utc_transition_times[-num_entries]:
    print(dt, dt.replace(tzinfo=datetime.timezone.utc).timestamp())
```
