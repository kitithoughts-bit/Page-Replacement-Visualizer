#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "algorithms.h"


void print_header(void)
{
    printf("\n");
    printf("==================================================\n");
    printf("       PAGE REPLACEMENT VISUALIZER\n");
    printf("==================================================\n");
}


void print_reference_string(
    const int reference[],
    int ref_count,
    int current_index
)
{
    printf("Reference String:\n\n");

    for (int i = 0;
         i < ref_count;
         i++) {

        if (i == current_index) {

            printf("[%d] ", reference[i]);
        }

        else {

            printf(" %d  ", reference[i]);
        }
    }

    printf("\n\n");
}


static void wait_for_enter(void)
{
    printf("\nPress ENTER for next step...");

    /*
     * Wait until ENTER is pressed.
     */
    int c;

    while ((c = getchar()) != '\n' &&
           c != EOF) {
    }
}


void print_step_simulation(
    const SimResult *result,
    const int reference[],
    const char *algorithm_name
)
{
    int current_faults = 0;
    int current_hits = 0;


    for (int i = 0;
         i < result->total_refs;
         i++) {

        SimStep step =
            result->steps[i];


        /*
         * Clear terminal.
         */

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif


        printf("==================================================\n");

        printf("          %s PAGE REPLACEMENT\n",
               algorithm_name);

        printf("==================================================\n\n");


        print_reference_string(
            reference,
            result->total_refs,
            i
        );


        printf("Step %d / %d\n",
               i + 1,
               result->total_refs);

        printf("Current Page : %d\n\n",
               step.page);


        printf("Memory Frames\n\n");


        for (int j = 0;
             j < result->num_frames;
             j++) {

            printf("        +-------------+\n");

            if (step.frames[j]
                == EMPTY_FRAME) {

                printf(
                    "Frame %-2d|      -      |\n",
                    j + 1
                );
            }

            else {

                printf(
                    "Frame %-2d|      %-5d  |\n",
                    j + 1,
                    step.frames[j]
                );
            }
        }


        printf("        +-------------+\n\n");


        /*
         * Fault or Hit
         */

        if (step.is_fault) {

            current_faults++;

            printf(">> PAGE FAULT\n");


            if (step.replaced_page
                != EMPTY_FRAME) {

                printf(
                    ">> Replaced Page : %d\n",
                    step.replaced_page
                );
            }
        }

        else {

            current_hits++;

            printf(">> PAGE HIT\n");
        }


        printf("\n");

        printf(
            "Faults : %d\n",
            current_faults
        );

        printf(
            "Hits   : %d\n",
            current_hits
        );


        /*
         * Don't wait after final step.
         */

        if (i <
            result->total_refs - 1) {

            wait_for_enter();
        }
    }


    printf(
        "\nSimulation complete.\n"
    );
}


void print_simulation_table(
    const SimResult *result,
    const char *algorithm_name
)
{
    printf("\n");

    printf(
        "========================================\n"
    );

    printf(
        "          %s SIMULATION TABLE\n",
        algorithm_name
    );

    printf(
        "========================================\n\n"
    );


    printf("Ref\t");


    for (int i = 0;
         i < result->num_frames;
         i++) {

        printf(
            "F%d\t",
            i + 1
        );
    }


    printf(
        "Result\tReplaced\n"
    );


    printf(
        "------------------------------------------------------------\n"
    );


    for (int i = 0;
         i < result->total_refs;
         i++) {

        SimStep step =
            result->steps[i];


        printf(
            "%d\t",
            step.page
        );


        for (int j = 0;
             j < result->num_frames;
             j++) {

            if (step.frames[j]
                == EMPTY_FRAME) {

                printf("-\t");
            }

            else {

                printf(
                    "%d\t",
                    step.frames[j]
                );
            }
        }


        if (step.is_fault) {

            printf("FAULT\t");
        }

        else {

            printf("HIT\t");
        }


        if (step.replaced_page
            == EMPTY_FRAME) {

            printf("-\n");
        }

        else {

            printf(
                "%d\n",
                step.replaced_page
            );
        }
    }
}


int input_display_mode(void)
{
    int choice;


    printf("\n");
    printf("Display Mode\n");
    printf("-----------------------\n");

    printf(
        "1. Step-by-Step Simulation\n"
    );

    printf(
        "2. Full Table\n"
    );

    printf(
        "3. Both\n"
    );


    printf("\nSelect: ");


    if (scanf("%d", &choice) != 1) {

        /*
         * Clear invalid input.
         */

        int c;

        while ((c = getchar()) != '\n' &&
               c != EOF) {
        }

        return 3;
    }


    /*
     * Remove newline left by scanf.
     */

    int c;

    while ((c = getchar()) != '\n' &&
           c != EOF) {
    }


    if (choice < 1 ||
        choice > 3) {

        choice = 3;
    }


    return choice;
}