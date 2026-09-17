#ifndef IO_H
#define IO_H

#include "common.h"

void print_header(void);
void print_main_menu(void);

int input_frame_count(void);

int input_reference_string(
    int reference[],
    int max_size
);

int generate_random_reference(
    int reference[],
    int count,
    int max_page
);

int read_reference_file(
    const char *filename,
    int reference[],
    int max_size
);

int input_algorithm(void);

void print_frames(
    const Frame frames[],
    int frame_count
);

void print_simulation(
    const SimResult *result
);

#endif