#ifndef STATS_H
#define STATS_H

#include "common.h"


double calculate_hit_ratio(
    const SimResult *result
);


double calculate_fault_ratio(
    const SimResult *result
);


void print_statistics(
    const SimResult *result
);


#endif