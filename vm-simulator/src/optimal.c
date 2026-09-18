#include "../include/algorithms.h"
static int find_victim(
    Frame frames[],
    int frame_count,
    const int reference[],
    int ref_count,
    int current
) {
    int victim = 0;
    int farthest = -1;
    for (int j = 0; j < frame_count; j++) {
        int next_use = ref_count;   
        for (int k = current + 1; k < ref_count; k++) {
            if (reference[k] == frames[j].page) {
                next_use = k;
                break;
            }
        }
        if (next_use == ref_count) {
            return j;
        }
        if (next_use > farthest) {
            farthest = next_use;
            victim = j;
        }
    }
    return victim;
}
SimResult run_optimal(
    const int reference[],
    int ref_count,
    int frame_count
) {
    SimResult result;
    Frame frames[MAX_FRAMES];
    result.faults = 0;
    result.hits = 0;
    result.total_refs = ref_count;
    result.num_frames = frame_count;
    for (int i = 0; i < frame_count; i++) {
        frames[i].page = EMPTY_FRAME;
        frames[i].valid = 0;
    }
    for (int i = 0; i < ref_count; i++) {
        int current_page = reference[i];
        int found = 0;
        for (int j = 0; j < frame_count; j++) {
            if (frames[j].valid &&
                frames[j].page == current_page) {
                found = 1;
                break;
            }
        }
        result.steps[i].page = current_page;
        result.steps[i].replaced_page = EMPTY_FRAME;
        if (found) {
            result.hits++;
            result.steps[i].is_fault = 0;
        } else {
            result.faults++;
            result.steps[i].is_fault = 1;
            int target = -1;
            for (int j = 0; j < frame_count; j++) {
                if (!frames[j].valid) {
                    target = j;
                    break;
                }
            }
            if (target == -1) {
                target = find_victim(
                    frames, frame_count,
                    reference, ref_count, i
                );
                result.steps[i].replaced_page =
                    frames[target].page;
            }
            frames[target].page = current_page;
            frames[target].valid = 1;
        }
        for (int j = 0; j < frame_count; j++) {
            if (frames[j].valid) {
                result.steps[i].frames[j] = frames[j].page;
            } else {
                result.steps[i].frames[j] = EMPTY_FRAME;
            }
        }
    }
    return result;
}