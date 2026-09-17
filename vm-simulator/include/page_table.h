#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include "common.h"

typedef struct {
    int frame;
    int valid;
} PageTableEntry;

void page_table_init(
    PageTableEntry page_table[],
    int page_count
);

int page_table_lookup(
    PageTableEntry page_table[],
    int page
);

void page_table_update(
    PageTableEntry page_table[],
    int page,
    int frame
);

void page_table_remove(
    PageTableEntry page_table[],
    int page
);

#endif