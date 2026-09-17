#include "../include/algorithms.h"

SimResult run_fifo(
    const int reference[],
    int ref_count,
    int frame_count
) {
    SimResult result;

    Frame frames[MAX_FRAMES];

    int next_replace = 0;

    result.faults = 0;
    result.hits = 0;
    result.total_refs = ref_count;
    result.num_frames = frame_count;

    // Initialize frames
    for (int i = 0; i < frame_count; i++) {
        frames[i].page = EMPTY_FRAME;
        frames[i].valid = 0;
    }

    // Process each reference
    for (int i = 0; i < ref_count; i++) {

        int current_page = reference[i];

        int found = 0;

        // Check if page already exists in frame
        for (int j = 0; j < frame_count; j++) {

            if (frames[j].valid &&
                frames[j].page == current_page) {

                found = 1;
                break;
            }
        }

        result.steps[i].page = current_page;
        result.steps[i].replaced_page = EMPTY_FRAME;

        // Page Hit
        if (found) {

            result.hits++;

            result.steps[i].is_fault = 0;

        }

        // Page Fault
        else {

            result.faults++;

            result.steps[i].is_fault = 1;

            // If target frame already contains a page,
            // remember which page is replaced
            if (frames[next_replace].valid) {
                result.steps[i].replaced_page =
                    frames[next_replace].page;
            }

            // Replace page
            frames[next_replace].page = current_page;
            frames[next_replace].valid = 1;

            // Move FIFO pointer
            next_replace =
                (next_replace + 1) % frame_count;
        }

        // Save frame state after this step
        for (int j = 0; j < frame_count; j++) {

            if (frames[j].valid) {
                result.steps[i].frames[j] =
                    frames[j].page;
            } else {
                result.steps[i].frames[j] =
                    EMPTY_FRAME;
            }
        }
    }

    return result;
}