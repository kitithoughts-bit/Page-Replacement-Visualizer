#ifndef IO_H
#define IO_H

#include "common.h"

void print_header(void);

int input_frame_count(void);

int input_reference_string(
    int reference[],
    int max_size
);

int input_algorithm(void);

void print_frames(
    Frame frames[],
    int frame_count
);

#endif