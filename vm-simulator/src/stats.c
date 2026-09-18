#include <stdio.h>

#include "stats.h"


double calculate_hit_ratio(
    const SimResult *result
)
{
    if (result->total_refs == 0) {
        return 0.0;
    }

    return
        ((double) result->hits /
         result->total_refs) * 100.0;
}


double calculate_fault_ratio(
    const SimResult *result
)
{
    if (result->total_refs == 0) {
        return 0.0;
    }

    return
        ((double) result->faults /
         result->total_refs) * 100.0;
}


void print_statistics(
    const SimResult *result
)
{
    printf("\n");
    printf("========================================\n");
    printf("              FINAL RESULT\n");
    printf("========================================\n\n");

    printf("Total References : %d\n",
           result->total_refs);

    printf("Number of Frames : %d\n",
           result->num_frames);

    printf("Page Faults      : %d\n",
           result->faults);

    printf("Page Hits        : %d\n",
           result->hits);

    printf("Fault Ratio      : %.2f%%\n",
           calculate_fault_ratio(result));

    printf("Hit Ratio        : %.2f%%\n",
           calculate_hit_ratio(result));

    printf("\n");
}