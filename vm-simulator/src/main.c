#include <stdio.h>

#include "../include/common.h"
#include "../include/algorithms.h"

int main(void)
{
    // ========================================
    // Reference String
    // ========================================

    int reference[] = {
        7, 0, 1, 2, 0, 3, 0, 4, 2, 3
    };

    int ref_count =
        sizeof(reference) / sizeof(reference[0]);

    int frame_count = 3;


    // ========================================
    // Run LRU
    // ========================================

    SimResult result =
        run_lru(
            reference,
            ref_count,
            frame_count
        );


    // ========================================
    // Header
    // ========================================

    printf("LRU Simulation\n\n");


    // ========================================
    // Table Header
    // ========================================

    printf("Ref\t");

    for (int i = 0;
         i < frame_count;
         i++)
    {
        printf("F%d\t", i + 1);
    }

    printf("Result\tReplaced\n");

    printf("----------------------------------------\n");


    // ========================================
    // แสดงแต่ละ Step
    // ========================================

    for (int i = 0;
         i < result.total_refs;
         i++)
    {
        // Reference
        printf("%d\t",
               result.steps[i].page);


        // Frames
        for (int j = 0;
             j < result.num_frames;
             j++)
        {
            if (result.steps[i].frames[j]
                == EMPTY_FRAME)
            {
                printf("-\t");
            }
            else
            {
                printf("%d\t",
                       result.steps[i].frames[j]);
            }
        }


        // HIT / FAULT
        if (result.steps[i].is_fault)
        {
            printf("FAULT\t");
        }
        else
        {
            printf("HIT\t");
        }


        // Replaced Page
        if (result.steps[i].replaced_page
            == EMPTY_FRAME)
        {
            printf("-\n");
        }
        else
        {
            printf("%d\n",
                   result.steps[i].replaced_page);
        }
    }


    // ========================================
    // Summary
    // ========================================

    printf("\nPage Faults : %d\n",
           result.faults);

    printf("Page Hits   : %d\n",
           result.hits);


    return 0;
}

