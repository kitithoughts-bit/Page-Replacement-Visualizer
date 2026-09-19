#ifndef IO_H
#define IO_H

#include "common.h"

void print_header(void);

int input_reference_string(
    int reference[],
    int max_size
);

int input_frame_count(void);

int input_algorithm(void);

int input_display_mode(void);

void print_reference_string_with_marks(
    const int reference[],
    int ref_count,
    const SimResult *result,
    int current_index
);

void print_step_simulation(
    const SimResult *result,
    const int reference[],
    const char *algorithm_name
);

void print_simulation_table(
    const SimResult *result,
    const char *algorithm_name
);

#endif