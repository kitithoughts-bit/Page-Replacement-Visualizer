#include "algorithms.h"

SimResult run_lfu(
    const int reference[],
    int ref_count,
    int frame_count
)
{
    SimResult result;

    Frame frames[MAX_FRAMES];

    int frequency[MAX_FRAMES];
    int arrival_time[MAX_FRAMES];

    int time = 0;

    result.faults = 0;
    result.hits = 0;
    result.total_refs = ref_count;
    result.num_frames = frame_count;

    /* Initialize frames */
    for (int i = 0; i < frame_count; i++) {
        frames[i].page = EMPTY_FRAME;
        frames[i].valid = 0;

        frequency[i] = 0;
        arrival_time[i] = 0;
    }

    for (int i = 0; i < ref_count; i++) {

        int current_page = reference[i];

        int found_index = -1;

        result.steps[i].page = current_page;
        result.steps[i].replaced_page = EMPTY_FRAME;

        /* Check if page is already in memory */
        for (int j = 0; j < frame_count; j++) {

            if (frames[j].valid &&
                frames[j].page == current_page) {

                found_index = j;
                break;
            }
        }

        /* PAGE HIT */
        if (found_index != -1) {

            result.hits++;
            result.steps[i].is_fault = 0;

            frequency[found_index]++;
        }

        /* PAGE FAULT */
        else {

            result.faults++;
            result.steps[i].is_fault = 1;

            int target = -1;

            /* First try to find an empty frame */
            for (int j = 0; j < frame_count; j++) {

                if (!frames[j].valid) {
                    target = j;
                    break;
                }
            }

            /*
             * If memory is full,
             * find LFU victim.
             */
            if (target == -1) {

                target = 0;

                for (int j = 1; j < frame_count; j++) {

                    if (frequency[j] < frequency[target]) {

                        target = j;
                    }

                    /*
                     * Tie:
                     * replace the page that entered earlier.
                     */
                    else if (
                        frequency[j] == frequency[target] &&
                        arrival_time[j] < arrival_time[target]
                    ) {
                        target = j;
                    }
                }

                result.steps[i].replaced_page =
                    frames[target].page;
            }

            /* Insert new page */
            frames[target].page = current_page;
            frames[target].valid = 1;

            frequency[target] = 1;

            arrival_time[target] = time;
            time++;
        }

        /* Save frame state */
        for (int j = 0; j < frame_count; j++) {

            if (frames[j].valid) {
                result.steps[i].frames[j] =
                    frames[j].page;
            }
            else {
                result.steps[i].frames[j] =
                    EMPTY_FRAME;
            }
        }
    }

    return result;
}