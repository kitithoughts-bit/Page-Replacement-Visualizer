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


double calculate_hit_ratio(
    const SimResult *result
) {
    if (result->total_refs == 0) {
        return 0.0;
    }
    return (double) result->hits
         / (double) result->total_refs * 100.0;
}

double calculate_fault_ratio(
    const SimResult *result
) {
    if (result->total_refs == 0) {
        return 0.0;
    }
    return (double) result->faults
         / (double) result->total_refs * 100.0;
}

void stats_print(
    const SimResult *result
) {
    printf("\n");
    printf("Statistics\n");
    printf("----------------------------------------\n");
    printf("Total References : %d\n", result->total_refs);
    printf("Frames           : %d\n", result->num_frames);
    printf("Page Faults      : %d\n", result->faults);
    printf("Page Hits        : %d\n", result->hits);
    printf("Hit Ratio        : %.2f%%\n",
           calculate_hit_ratio(result));
    printf("Fault Ratio      : %.2f%%\n",
           calculate_fault_ratio(result));
    printf("----------------------------------------\n");
}

void stats_compare(
    const SimResult *fifo,
    const SimResult *lru,
    const SimResult *optimal
) {
    printf("\n");
    printf("Algorithm Comparison\n");
    printf("--------------------------------------------------\n");
    printf("%-10s %-8s %-8s %-12s\n",
           "Algorithm", "Faults", "Hits", "Hit Ratio");
    printf("--------------------------------------------------\n");

    printf("%-10s %-8d %-8d %-11.2f%%\n",
           "FIFO", fifo->faults, fifo->hits,
           calculate_hit_ratio(fifo));

    printf("%-10s %-8d %-8d %-11.2f%%\n",
           "LRU", lru->faults, lru->hits,
           calculate_hit_ratio(lru));

    printf("%-10s %-8d %-8d %-11.2f%%\n",
           "Optimal", optimal->faults, optimal->hits,
           calculate_hit_ratio(optimal));

    printf("--------------------------------------------------\n");

    int best = fifo->faults;
    const char *name = "FIFO";

    if (lru->faults < best)     { best = lru->faults;     name = "LRU"; }
    if (optimal->faults < best) { best = optimal->faults; name = "Optimal"; }

    printf("Best (fewest faults): %s (%d faults)\n", name, best);
    printf("--------------------------------------------------\n");

}