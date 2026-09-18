#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/common.h"
#include "../include/io.h"



void print_header(void)
{
    printf("========================================\n");
    printf(" Virtual Memory & Page Replacement\n");
    printf(" Simulator\n");
    printf("========================================\n\n");
}



void print_main_menu(void)
{
    printf("========== Main Menu ==========\n");
    printf("1. Enter Reference String\n");
    printf("2. Generate Random Reference String\n");
    printf("3. Select Algorithm\n");
    printf("4. Exit\n");
    printf("===============================\n");
}



int input_frame_count(void)
{
    int frame_count;

    do {

        printf("Enter number of frames (1-%d): ",
            MAX_FRAMES);

        scanf("%d", &frame_count);

        if (frame_count < 1 ||
            frame_count > MAX_FRAMES) {

            printf("Invalid frame count!\n");
        }

    } while (frame_count < 1 ||
            frame_count > MAX_FRAMES);

    return frame_count;
}



int input_reference_string(
    int *reference[],
    int *max_size
)
{
    int count;

    printf("Enter number of references (1-%d): ",
           *max_size);

    scanf("%d", &count);

    if (count < 1 ||
        count > *max_size) {

        printf("Invalid reference count!\n");
        return 0;
    }

    /*
     * รับ page reference ทีละตัว
     */
    for (int i = 0; i < count; i++) {

        int page;

        printf("Reference %d: ", i + 1);

        scanf("%d", &page);

        /*
         * ตรวจสอบ page number
         */
        if (page < 0 ||
            page >= MAX_PAGES) {

            printf("Invalid page number!\n");
            return 0;
        }

        reference[i] = malloc(sizeof(int));

        if (reference[i] == NULL) {
            printf("Memory allocation failed!\n");
            return 0;
        }

        *reference[i] = page;
    }


    return count;
}



int generate_random_reference(
    int *reference[],
    int *count,
    int *max_page
)
{
    if (*count < 1 ||
        *count > MAX_REF) {

        return 0;
    }

    if (*max_page < 1 ||
        *max_page > MAX_PAGES) {

        return 0;
    }

    srand((unsigned int)time(NULL));

    for (int i = 0; i < *count; i++) {

        reference[i] = malloc(sizeof(int));

        if (reference[i] == NULL) {
            return 0;
        }


        *reference[i] =
            rand() % *max_page;
    }

    return 1;
}



int read_reference_file(
    const char **filename,
    int *reference[],
    int *max_size
)
{
    FILE *file;

    file = fopen(*filename, "r");

    if (file == NULL) {

        printf("Cannot open file: %s\n",
               *filename);

        return 0;
    }

    int count = 0;
    int page;

    while (count < *max_size &&
        fscanf(file, "%d", &page) == 1) {

        if (page < 0 ||
            page >= MAX_PAGES) {

            printf("Invalid page number: %d\n",
                page);

            fclose(file);
            return 0;
        }

        reference[count] =
            malloc(sizeof(int));

        if (reference[count] == NULL) {

            fclose(file);
            return 0;
        }

        *reference[count] = page;

        count++;
    }

    fclose(file);

    return count;
}



int input_algorithm(void)
{
    int choice;

    do {

        printf("\n========== Algorithm ==========\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Optimal\n");
        printf("===============================\n");

        printf("Choose algorithm: ");

        scanf("%d", &choice);

        if (choice < 1 ||
            choice > 3) {

            printf("Invalid choice!\n");
        }

    } while (choice < 1 ||
            choice > 3);

    return choice;
}


/*
 * แสดง Frame ปัจจุบัน
 */
void print_frames(
    const Frame *frames[],
    int *frame_count
)
{
    for (int i = 0;
         i < *frame_count;
        i++) {

        if (frames[i]->valid) {

            printf("%d\t",
                frames[i]->page);

        } else {

            printf("-\t");
        }
    }
}



void print_simulation(
    const SimResult **result
)
{
    if (result == NULL ||
        *result == NULL) {

        printf("No simulation result.\n");
        return;
    }

    printf("\nSimulation\n\n");

    /*
     * Header
     */
    printf("Ref\t");

    for (int i = 0;
        i < (*result)->num_frames;
        i++) {

        printf("F%d\t", i + 1);
    }

    printf("Result\tReplaced\n");

    printf("----------------------------------------\n");



    for (int i = 0;
        i < (*result)->total_refs;
        i++) {

        SimStep *step = &(*result)->steps[i];

        /*
         * Reference
         */
        printf("%d\t",
            step->page);


        /*
         * Frame state
         */
        for (int j = 0;
            j < (*result)->num_frames;
            j++) {

            if (step->frames[j] ==
                EMPTY_FRAME) {

                printf("-\t");

            } else {

                printf("%d\t",
                    step->frames[j]);
            }
        }


        /*
         * HIT / FAULT
         */
        if (step->is_fault) {

            printf("FAULT\t");

        } else {

            printf("HIT\t");
        }


        /*
         * Replaced Page
         */
        if (step->replaced_page ==
            EMPTY_FRAME) {

            printf("-\n");

        } else {

            printf("%d\n",
                step->replaced_page);
        }
    }


    /*
     * Summary
     */
    printf("\nPage Faults : %d\n",
        (*result)->faults);

    printf("Page Hits   : %d\n",
        (*result)->hits);

    /*
     * Ratio
     */
    if ((*result)->total_refs > 0) {

        double fault_ratio =
            (double)(*result)->faults /
            (*result)->total_refs * 100.0;

        double hit_ratio =
            (double)(*result)->hits /
            (*result)->total_refs * 100.0;

        printf("Fault Ratio : %.2f%%\n",
            fault_ratio);

        printf("Hit Ratio   : %.2f%%\n",
            hit_ratio);
    }
}