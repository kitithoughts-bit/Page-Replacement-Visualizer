#ifndef IO_H
#define IO_H

#include "common.h"

void print_header(void);

void print_reference_string(
    const int reference[],
    int ref_count,
    int current_index
);

int input_algorithm(void);

int input_display_mode(void);

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