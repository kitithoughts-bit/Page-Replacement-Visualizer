#include <stdio.h>
#include "stats.h"


double calculate_hit_ratio(
    const SimResult *result
)
{
    if (result->total_refs == 0) {
        return 0.0;
    }

    return ((double) result->hits /
            result->total_refs) * 100.0;
}


double calculate_fault_ratio(
    const SimResult *result
)
{
    if (result->total_refs == 0) {
        return 0.0;
    }

    return ((double) result->faults /
            result->total_refs) * 100.0;
}


void stats_print(
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


void stats_compare(
    const SimResult *fifo,
    const SimResult *lru,
    const SimResult *optimal,
    const SimResult *lfu
)
{
    printf("\n");

    printf("============================================================\n");
    printf("                  ALGORITHM COMPARISON\n");
    printf("============================================================\n\n");

    printf(
        "%-12s %-10s %-10s %-12s %-12s\n",
        "Algorithm",
        "Faults",
        "Hits",
        "Hit Ratio",
        "Fault Ratio"
    );

    printf(
        "------------------------------------------------------------\n"
    );


    printf(
        "%-12s %-10d %-10d %-11.2f%% %-11.2f%%\n",
        "FIFO",
        fifo->faults,
        fifo->hits,
        calculate_hit_ratio(fifo),
        calculate_fault_ratio(fifo)
    );


    printf(
        "%-12s %-10d %-10d %-11.2f%% %-11.2f%%\n",
        "LRU",
        lru->faults,
        lru->hits,
        calculate_hit_ratio(lru),
        calculate_fault_ratio(lru)
    );


    printf(
        "%-12s %-10d %-10d %-11.2f%% %-11.2f%%\n",
        "Optimal",
        optimal->faults,
        optimal->hits,
        calculate_hit_ratio(optimal),
        calculate_fault_ratio(optimal)
    );


    printf(
        "%-12s %-10d %-10d %-11.2f%% %-11.2f%%\n",
        "LFU",
        lfu->faults,
        lfu->hits,
        calculate_hit_ratio(lfu),
        calculate_fault_ratio(lfu)
    );


    printf(
        "------------------------------------------------------------\n"
    );
}