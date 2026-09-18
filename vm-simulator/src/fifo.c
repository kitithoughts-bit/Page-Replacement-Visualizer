#include "algorithms.h"


SimResult run_fifo(
    const int reference[],
    int ref_count,
    int frame_count
)
{
    SimResult result;

    Frame frames[MAX_FRAMES];

    /*
     * Points to the next frame that will
     * be replaced according to FIFO.
     */
    int next_replace = 0;


    /* Initialize result */

    result.faults = 0;
    result.hits = 0;

    result.total_refs = ref_count;
    result.num_frames = frame_count;


    /* Initialize all frames as empty */

    for (int i = 0; i < frame_count; i++) {

        frames[i].page = EMPTY_FRAME;
        frames[i].valid = 0;
    }


    /* Process reference string */

    for (int i = 0; i < ref_count; i++) {

        int current_page = reference[i];

        int found = 0;


        /* Check if page is already in memory */

        for (int j = 0;
             j < frame_count;
             j++) {

            if (frames[j].valid &&
                frames[j].page == current_page) {

                found = 1;
                break;
            }
        }


        /* Store basic step information */

        result.steps[i].page =
            current_page;

        result.steps[i].replaced_page =
            EMPTY_FRAME;


        /*
         * PAGE HIT
         */

        if (found) {

            result.hits++;

            result.steps[i].is_fault = 0;
        }


        /*
         * PAGE FAULT
         */

        else {

            result.faults++;

            result.steps[i].is_fault = 1;


            /*
             * If this frame already contains
             * a page, remember which page
             * is being removed.
             */

            if (frames[next_replace].valid) {

                result.steps[i].replaced_page =
                    frames[next_replace].page;
            }


            /*
             * Put new page into memory.
             */

            frames[next_replace].page =
                current_page;

            frames[next_replace].valid = 1;


            /*
             * Move FIFO pointer.
             *
             * Example with 3 frames:
             *
             * 0 -> 1 -> 2 -> 0 -> ...
             */

            next_replace =
                (next_replace + 1)
                % frame_count;
        }


        /*
         * Save current frame state
         * into simulation history.
         */

        for (int j = 0;
             j < frame_count;
             j++) {

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