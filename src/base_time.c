#include "base_time.h"
#include <time.h>

f64 time_now() {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (f64)ts.tv_sec + (f64)ts.tv_nsec / 1e9;
}
