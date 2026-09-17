#ifndef STATS_H
#define STATS_H

#include "common.h"

double calculate_hit_ratio(
    const SimResult *result
);

double calculate_fault_ratio(
    const SimResult *result
);

void stats_print(
    const SimResult *result
);

void stats_compare(
    const SimResult *fifo,
    const SimResult *lru,
    const SimResult *optimal
);

#endif