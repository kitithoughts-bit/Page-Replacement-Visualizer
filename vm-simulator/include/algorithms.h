#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "common.h"

typedef struct {
    int page;
    int valid;
    int reference_bit;
} ClockFrame;

int fifo_select_victim(
    Frame frames[],
    int frame_count
);

int lru_select_victim(
    Frame frames[],
    int frame_count,
    int last_used[]
);

int optimal_select_victim(
    Frame frames[],
    int frame_count,
    int reference[],
    int ref_count,
    int current_index
);

#endif