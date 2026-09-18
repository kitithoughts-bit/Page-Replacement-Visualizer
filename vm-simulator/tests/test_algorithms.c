#include <stdio.h>

#include "../include/common.h"
#include "../include/algorithms.h"

static int tests_run = 0;
static int tests_passed = 0;

static void check(const char *name, int got, int expected)
{
    tests_run++;
    if (got == expected) {
        tests_passed++;
        printf("[PASS] %-28s got=%d\n", name, got);
    } else {
        printf("[FAIL] %-28s got=%d expected=%d\n",
               name, got, expected);
    }
}

int main(void)
{
    int textbook[] = {
        7, 0, 1, 2, 0, 3, 0, 4, 2, 3,
        0, 3, 2, 1, 2, 0, 1, 7, 0, 1
    };
    int n1 = sizeof(textbook) / sizeof(textbook[0]);

    check("FIFO textbook (3f)",    run_fifo(textbook, n1, 3).faults, 15);
    check("LRU textbook (3f)",     run_lru(textbook, n1, 3).faults, 12);
    check("Optimal textbook (3f)", run_optimal(textbook, n1, 3).faults, 9);

    int belady[] = { 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5 };
    int n2 = sizeof(belady) / sizeof(belady[0]);

    check("FIFO belady (3f)", run_fifo(belady, n2, 3).faults, 9);
    check("FIFO belady (4f)", run_fifo(belady, n2, 4).faults, 10);

    check("Optimal <= FIFO (belady 3f)",
          run_optimal(belady, n2, 3).faults
              <= run_fifo(belady, n2, 3).faults, 1);

    int same[] = { 5, 5, 5, 5, 5 };
    check("Optimal all-same", run_optimal(same, 5, 3).faults, 1);

    SimResult r = run_optimal(textbook, n1, 3);
    check("Optimal hits+faults==total",
          r.hits + r.faults, r.total_refs);

    printf("\n%d/%d tests passed.\n", tests_passed, tests_run);
    return (tests_passed == tests_run) ? 0 : 1;
}