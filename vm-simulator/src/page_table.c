#include "page_table.h"

void page_table_init(
    PageTableEntry page_table[],
    int page_count
)
{
    for (int i = 0; i < page_count; i++) {
        page_table[i].frame = EMPTY_FRAME;
        page_table[i].valid = 0;
    }
}

int page_table_lookup(
    const PageTableEntry page_table[],
    int page
)
{
    if (page < 0 || page >= MAX_PAGES) {
        return EMPTY_FRAME;
    }

    if (page_table[page].valid == 0) {
        return EMPTY_FRAME;
    }

    return page_table[page].frame;
}

void page_table_update(
    PageTableEntry page_table[],
    int page,
    int frame
)
{
    if (page < 0 || page >= MAX_PAGES) {
        return;
    }

    page_table[page].frame = frame;
    page_table[page].valid = 1;
}

void page_table_remove(
    PageTableEntry page_table[],
    int page
)
{
    if (page < 0 || page >= MAX_PAGES) {
        return;
    }

    page_table[page].frame = EMPTY_FRAME;
    page_table[page].valid = 0;
}