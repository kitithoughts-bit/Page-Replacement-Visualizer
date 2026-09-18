#include <stdio.h>

#include "common.h"
#include "algorithms.h"
#include "io.h"
#include "stats.h"

int main(void)
{
    int reference[] = {
        7, 0, 1, 2, 0,
        3, 0, 4, 2, 3
    };

    int ref_count =
        sizeof(reference) / sizeof(reference[0]);

    int frame_count = 3;

    print_header();

    printf("\nFrames    : %d\n", frame_count);

    printf("References: ");

    for (int i = 0; i < ref_count; i++) {
        printf("%d ", reference[i]);
    }

    printf("\n");

    /*
     * Select algorithm
     */
    int algorithm_choice =
        input_algorithm();

    SimResult result;

    const char *algorithm_name;

    /*
     * Run selected algorithm
     */
    switch (algorithm_choice)
    {
        case 1:
            result = run_fifo(
                reference,
                ref_count,
                frame_count
            );

            algorithm_name = "FIFO";
            break;

        case 2:
            result = run_lru(
                reference,
                ref_count,
                frame_count
            );

            algorithm_name = "LRU";
            break;

        case 3:
            printf("\nOptimal is not implemented yet.\n");
            return 0;

            algorithm_name = "OPTIMAL";
            break;

        default:
            result = run_fifo(
                reference,
                ref_count,
                frame_count
            );

            algorithm_name = "FIFO";
            break;
    }

    /*
     * Select display mode
     */
    int display_mode =
        input_display_mode();

    switch (display_mode)
    {
        case 1:
            print_step_simulation(
                &result,
                reference,
                algorithm_name
            );
            break;

        case 2:
            print_simulation_table(
                &result,
                algorithm_name
            );
            break;

        case 3:
        default:
            print_step_simulation(
                &result,
                reference,
                algorithm_name
            );

            print_simulation_table(
                &result,
                algorithm_name
            );
            break;
    }

    print_statistics(&result);

    return 0;
}