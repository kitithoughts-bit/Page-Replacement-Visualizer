#ifndef STATS_H
#define STATS_H

typedef struct {
    int total_references;
    int page_hits;
    int page_faults;
} Stats;

void stats_init(Stats *stats);

void stats_record_hit(Stats *stats);

void stats_record_fault(Stats *stats);

void stats_print(const Stats *stats);

#endif