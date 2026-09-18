#ifndef COMMON_H
#define COMMON_H

#define MAX_PAGES 100
#define MAX_FRAMES 20
#define MAX_REF 100

#define EMPTY_FRAME -1

/* Physical memory frame */
typedef struct {
    int page;
    int valid;
} Frame;


/* Result of one simulation step */
typedef struct {
    int page;

    int frames[MAX_FRAMES];

    int is_fault;

    /*
     * Page that was removed from memory.
     * EMPTY_FRAME means no page was replaced.
     */
    int replaced_page;

} SimStep;


/* Complete result of one page replacement simulation */
typedef struct {

    int faults;
    int hits;

    int total_refs;
    int num_frames;

    SimStep steps[MAX_REF];

} SimResult;


#endif