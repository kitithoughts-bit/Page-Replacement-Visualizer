#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "common.h"

SimResult run_fifo(
    const int reference[],
    int ref_count,
    int frame_count
);

SimResult run_lru(
    const int reference[],
    int ref_count,
    int frame_count
);

SimResult run_optimal(
    const int reference[],
    int ref_count,
    int frame_count
);

#endif