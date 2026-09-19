#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "algorithms.h"

/* ANSI Colors */
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_BOLD    "\033[1m"

void print_header(void)
{
    printf("\n");
    printf("==================================================\n");
    printf("         PAGE REPLACEMENT VISUALIZER\n");
    printf("==================================================\n");
}


static void clear_input_buffer(void)
{
    int c;

    while ((c = getchar()) != '\n' &&
           c != EOF) {
    }
}


int input_reference_string(
    int reference[],
    int max_size
)
{
    char line[1024];
    int count = 0;

    printf("\nEnter Reference String\n");
    printf("(separate numbers with spaces)\n");
    printf("Example: 7 0 1 2 0 3 0 4 2 3\n");
    printf("Input: ");

    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 0;
    }

    char *token = strtok(line, " ,\t\r\n");

    while (token != NULL && count < max_size) {
        reference[count++] = atoi(token);
        token = strtok(NULL, " ,\t\r\n");
    }

    return count;
}


int input_frame_count(void)
{
    int frame_count;

    while (1) {
        printf("\nEnter Number of Frames (1-%d): ",
               MAX_FRAMES);

        if (scanf("%d", &frame_count) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }

        clear_input_buffer();

        if (frame_count < 1 ||
            frame_count > MAX_FRAMES) {
            printf("Frame count must be between 1 and %d.\n",
                   MAX_FRAMES);
            continue;
        }

        return frame_count;
    }
}


int input_algorithm(void)
{
    int choice;

    printf("\n");
    printf("Select Algorithm\n");
    printf("-----------------------------\n");
    printf("1. FIFO\n");
    printf("2. LRU\n");
    printf("3. Optimal\n");
    printf("4. LFU\n");
    printf("5. Compare All Algorithms\n");

    printf("\nSelect: ");

    if (scanf("%d", &choice) != 1) {

        int c;

        while ((c = getchar()) != '\n' &&
               c != EOF) {
        }

        return 1;
    }

    int c;

    while ((c = getchar()) != '\n' &&
           c != EOF) {
    }

    if (choice < 1 || choice > 5) {
        choice = 1;
    }

    return choice;
}


int input_display_mode(void)
{
    int choice;

    printf("\nDisplay Mode\n");
    printf("-----------------------\n");
    printf("1. Step-by-Step Simulation\n");
    printf("2. Full Table\n");
    printf("3. Both\n");

    printf("\nSelect: ");

    if (scanf("%d", &choice) != 1) {
        clear_input_buffer();
        return 3;
    }

    clear_input_buffer();

    if (choice < 1 || choice > 3) {
        choice = 3;
    }

    return choice;
}


static void wait_for_enter(void)
{
    printf("\nPress ENTER for next step...");
    getchar();
}


void print_reference_string_with_marks(
    const int reference[],
    int ref_count,
    const SimResult *result,
    int current_index
)
{
    printf(COLOR_BOLD "Reference String:\n\n" COLOR_RESET);

    /*
     * Reference values
     */
    printf("Page   : ");

    for (int i = 0; i < ref_count; i++) {

        if (i == current_index) {

            printf(
                COLOR_YELLOW
                "[%2d] "
                COLOR_RESET,
                reference[i]
            );
        }

        else {

            printf(
                " %2d  ",
                reference[i]
            );
        }
    }

    printf("\n");


    /*
     * F / H marks
     */
    printf("Status : ");

    for (int i = 0; i < ref_count; i++) {

        if (i <= current_index) {

            if (result->steps[i].is_fault) {

                printf(
                    COLOR_RED
                    "  F  "
                    COLOR_RESET
                );
            }

            else {

                printf(
                    COLOR_GREEN
                    "  H  "
                    COLOR_RESET
                );
            }
        }

        else {

            printf("  .  ");
        }
    }

    printf("\n");


    /*
     * Current step pointer
     */
    printf("        ");

    for (int i = 0; i < ref_count; i++) {

        if (i == current_index) {

            printf(
                COLOR_YELLOW
                "  ^  "
                COLOR_RESET
            );
        }

        else {

            printf("     ");
        }
    }

    printf("\n\n");

    printf(
        COLOR_RED "F" COLOR_RESET
        " = Fault   "
        COLOR_GREEN "H" COLOR_RESET
        " = Hit   "
        ". = Not processed\n\n"
    );
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

        SimStep step = result->steps[i];

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        printf("==================================================\n");

        printf(
            "              %s PAGE REPLACEMENT\n",
            algorithm_name
        );

        printf("==================================================\n\n");


        print_reference_string_with_marks(
            reference,
            result->total_refs,
            result,
            i
        );


        printf(
            COLOR_CYAN
            "Step %d / %d\n"
            COLOR_RESET,
            i + 1,
            result->total_refs
        );

        printf(
            "Current Page : %d\n",
            step.page
        );


        /*
         * Page Fault
         */
        if (step.is_fault) {

            current_faults++;

            printf(
                "Result       : "
                COLOR_RED
                "PAGE FAULT\n"
                COLOR_RESET
            );


            /*
             * Replacement occurred
             */
            if (step.replaced_page != EMPTY_FRAME) {

                printf(
                    "Replacement  : old page "
                    COLOR_RED "%d"
                    COLOR_RESET
                    " -> new page "
                    COLOR_YELLOW "%d"
                    COLOR_RESET
                    "\n",
                    step.replaced_page,
                    step.page
                );
            }

            /*
             * Empty frame
             */
            else {

                printf(
                    "Replacement  : none "
                    "(loaded page %d into an empty frame)\n",
                    step.page
                );
            }
        }


        /*
         * Page Hit
         */
        else {

            current_hits++;

            printf(
                "Result       : "
                COLOR_GREEN
                "PAGE HIT\n"
                COLOR_RESET
            );

            printf(
                "Replacement  : none "
                "(page %d is already in memory)\n",
                step.page
            );
        }


        printf("\n");

        printf(
            COLOR_BOLD
            "Memory Frames\n\n"
            COLOR_RESET
        );


        for (int j = 0;
             j < result->num_frames;
             j++) {

            printf(
                "        +-------------+\n"
            );


            if (step.frames[j] == EMPTY_FRAME) {

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


        printf(
            "        +-------------+\n"
        );


        printf("\n");

        printf(
            COLOR_RED
            "Faults : %d"
            COLOR_RESET
            "\n",
            current_faults
        );

        printf(
            COLOR_GREEN
            "Hits   : %d"
            COLOR_RESET
            "\n",
            current_hits
        );


        if (i < result->total_refs - 1) {
            wait_for_enter();
        }
    }


    printf(
        "\n"
        COLOR_GREEN
        "Simulation complete."
        COLOR_RESET
        "\n"
    );
}


void print_simulation_table(
    const SimResult *result,
    const char *algorithm_name
)
{
    printf("\n");
    printf("============================================================\n");
    printf("                   %s SIMULATION TABLE\n",
           algorithm_name);
    printf("============================================================\n\n");

    printf("Ref\t");

    for (int i = 0; i < result->num_frames; i++) {
        printf("F%d\t", i + 1);
    }

    printf("Result\tReplacement\n");

    printf("------------------------------------------------------------\n");

    for (int i = 0; i < result->total_refs; i++) {

        SimStep step = result->steps[i];

        printf("%d\t", step.page);

        for (int j = 0; j < result->num_frames; j++) {

            if (step.frames[j] == EMPTY_FRAME) {
                printf("-\t");
            }
            else {
                printf("%d\t", step.frames[j]);
            }
        }

        if (step.is_fault) {
            printf("FAULT\t");
        }
        else {
            printf("HIT\t");
        }

        if (step.replaced_page == EMPTY_FRAME) {
            printf("-\n");
        }
        else {
            printf("%d -> %d\n",
                   step.replaced_page,
                   step.page);
        }
    }

    printf("------------------------------------------------------------\n");
}