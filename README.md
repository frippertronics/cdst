# CDST - A DST libary in C

This repository provides a DST library for C-based projects which require
Daylight Saving Time functionality.

The library is based on current DST transitions as described by [Wikipedia](https://en.wikipedia.org/wiki/Daylight_saving_time_by_country). One exception is the Lord Howe Island in Australia.

As DST is a binary state, the library features one function that checks if the current time, expressed as
32-bit unsigned UNIX time, is within the specified country's DST window. The window is stored as part of the
library and is referenced by the country's [ISO 3166-1 numeric](https://en.wikipedia.org/wiki/ISO_3166-1_numeric) code.

Note: The library doesn't take into account local variations inside a country, like Hawaii which doesn't have DST.
The primary target for this library is embedded devices which don't have access to external clock sources, such as
online `tz`-databases.

To save space, the library can be compiled only for specific continents. This can be done by changing
the continent's option in the `CMakeLists.txt` or on the command-line with "-DDISABLE_ASIA_RULES=ON".
By default, _all_ DST rules are compiled.

Note: If a continent's rules are disabled, the library will _always_ return "false", i.e. "DST is not currently active".

# Requirements

- GCC
- CMake
- Ruby (testing only)

## Testing

For verification the library uses Unity and CTest to run a set of unit tests. The unit tests can be compiled by
changing the `BUILD_UNITTEST` option to `ON`.

## Test timestamp generation

Test timestamps for each country's transitions was generated using the following Python sequence:

```python
import pytz, datetime

tz = "Europe/Berlin"
num_entries = 30

for dt in pytz.timezone(tz)._utc_transition_times[-num_entries]:
    print(dt, dt.replace(tzinfo=datetime.timezone.utc).timestamp())
```
