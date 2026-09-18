#include <stdio.h>

#include "common.h"
#include "algorithms.h"
#include "io.h"
#include "stats.h"

int main(void)
{
    // ========================================
    // Reference String
    // ========================================

    int reference[] = {
        7, 0, 1, 2, 0,
        3, 0, 4, 2, 3
    };

    int ref_count =
        sizeof(reference) / sizeof(reference[0]);

    int frame_count = 3;

    /* -----------------------------
       Program Header
       ----------------------------- */
    print_header();

    printf("\nAlgorithm : FIFO\n");
    printf("Frames    : %d\n", frame_count);

    printf("References: ");

    for (int i = 0; i < ref_count; i++) {
        printf("%d ", reference[i]);
    }

    printf("\n");

    /* -----------------------------
       Run FIFO Algorithm
       ----------------------------- */
    SimResult result = run_fifo(
        reference,
        ref_count,
        frame_count
    );

    /* -----------------------------
       Select Display Mode
       ----------------------------- */
    int display_mode = input_display_mode();

    switch (display_mode)
    {
        case 1:
            /* Step-by-Step only */
            print_step_simulation(
                &result,
                reference,
                "FIFO"
            );
            break;

        case 2:
            /* Full Table only */
            print_simulation_table(
                &result,
                "FIFO"
            );
            break;

        case 3:
        default:
            /* Both */
            print_step_simulation(
                &result,
                reference,
                "FIFO"
            );

            print_simulation_table(
                &result,
                "FIFO"
            );
            break;
    }

    /* -----------------------------
       Final Statistics
       ----------------------------- */
    print_statistics(&result);

    return 0;

}
