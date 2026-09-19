#include <stdio.h>

#include "common.h"
#include "algorithms.h"
#include "io.h"
#include "stats.h"

int main(void)
{
    int reference[MAX_REF];
    int ref_count = 0;
    int frame_count = 0;

    int algorithm_choice;
    int display_mode;
    int next_action;

    SimResult result;
    const char *algorithm_name = NULL;

    print_header();

    while (1)
    {
        /*
         * Get new input
         */
        if (ref_count == 0)
        {
            ref_count = input_reference_string(
                reference,
                MAX_REF
            );

            if (ref_count <= 0)
            {
                printf("\nInvalid reference string.\n");
                continue;
            }

            frame_count = input_frame_count();
        }

        /*
         * Select algorithm
         */
        algorithm_choice = input_algorithm();

        /*
         * Compare all
         */
        if (algorithm_choice == 5)
        {
            SimResult fifo_result =
                run_fifo(
                    reference,
                    ref_count,
                    frame_count
                );

            SimResult lru_result =
                run_lru(
                    reference,
                    ref_count,
                    frame_count
                );

            SimResult optimal_result =
                run_optimal(
                    reference,
                    ref_count,
                    frame_count
                );

            SimResult lfu_result =
                run_lfu(
                    reference,
                    ref_count,
                    frame_count
                );

            stats_compare(
                &fifo_result,
                &lru_result,
                &optimal_result,
                &lfu_result
            );
        }

        /*
         * Single algorithm
         */
        else
        {
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
                    result = run_optimal(
                        reference,
                        ref_count,
                        frame_count
                    );

                    algorithm_name = "OPTIMAL";
                    break;

                case 4:
                    result = run_lfu(
                        reference,
                        ref_count,
                        frame_count
                    );

                    algorithm_name = "LFU";
                    break;

                default:
                    continue;
            }

            /*
             * Display Mode
             */
            display_mode = input_display_mode();

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

            stats_print(&result);
        }

        /*
         * Ask what to do next
         */
        printf("\n");
        printf("What would you like to do next?\n");
        printf("--------------------------------\n");
        printf("1. Choose another algorithm\n");
        printf("2. Enter new reference string and frames\n");
        printf("3. Exit\n");
        printf("\nSelect: ");

        if (scanf("%d", &next_action) != 1)
        {
            int c;

            while ((c = getchar()) != '\n' &&
                   c != EOF) {
            }

            next_action = 3;
        }
        else
        {
            int c;

            while ((c = getchar()) != '\n' &&
                   c != EOF) {
            }
        }

        /*
         * Choose another algorithm
         */
        if (next_action == 1)
        {
            continue;
        }

        /*
         * New input
         */
        else if (next_action == 2)
        {
            ref_count = 0;
            frame_count = 0;

            printf("\n");
            continue;
        }

        /*
         * Exit
         */
        else
        {
            printf("\n");
            printf("Do you want to exit? (y/n): ");

            char confirm;

            scanf(" %c", &confirm);

            int c;

            while ((c = getchar()) != '\n' &&
                   c != EOF) {
            }

            if (confirm == 'y' ||
                confirm == 'Y')
            {
                printf("\nThank you for using the simulator.\n");
                break;
            }

            /*
             * If user selects N,
             * return to algorithm menu
             */
            continue;
        }
    }

    return 0;
}