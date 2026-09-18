#include "../include/algorithms.h"

SimResult run_lru(
    const int reference[],
    int ref_count,
    int frame_count
)
{
    SimResult result;

    Frame frames[MAX_FRAMES];

    // เก็บตำแหน่งล่าสุดที่แต่ละ Frame ถูกใช้งาน
    int last_used[MAX_FRAMES];


    // ========================================
    // Initialize Result
    // ========================================

    result.faults = 0;
    result.hits = 0;
    result.total_refs = ref_count;
    result.num_frames = frame_count;


    // ========================================
    // Initialize Frames
    // ========================================

    for (int i = 0; i < frame_count; i++)
    {
        frames[i].page = EMPTY_FRAME;
        frames[i].valid = 0;

        // -1 = ยังไม่เคยถูกใช้งาน
        last_used[i] = -1;
    }


    // ========================================
    // Process Reference String
    // ========================================

    for (int i = 0; i < ref_count; i++)
    {
        int current_page = reference[i];

        int found = 0;
        int found_frame = -1;


        // ====================================
        // Check Page ใน Frame
        // ====================================

        for (int j = 0; j < frame_count; j++)
        {
            if (frames[j].valid &&
                frames[j].page == current_page)
            {
                found = 1;
                found_frame = j;

                break;
            }
        }


        // ====================================
        // บันทึกข้อมูล Step
        // ====================================

        result.steps[i].page = current_page;

        result.steps[i].replaced_page =
            EMPTY_FRAME;


        // ====================================
        // Page HIT
        // ====================================

        if (found)
        {
            result.hits++;

            result.steps[i].is_fault = 0;

            // อัปเดตว่า Frame นี้ถูกใช้งานล่าสุด
            last_used[found_frame] = i;
        }


        // ====================================
        // Page FAULT
        // ====================================

        else
        {
            result.faults++;

            result.steps[i].is_fault = 1;

            int target_frame = -1;


            // ------------------------------------
            // หา Frame ที่ยังว่าง
            // ------------------------------------

            for (int j = 0; j < frame_count; j++)
            {
                if (!frames[j].valid)
                {
                    target_frame = j;
                    break;
                }
            }


            // ------------------------------------
            // ถ้าไม่มี Frame ว่าง
            // หา LRU
            // ------------------------------------

            if (target_frame == -1)
            {
                int lru_frame = 0;

                for (int j = 1; j < frame_count; j++)
                {
                    if (last_used[j] <
                        last_used[lru_frame])
                    {
                        lru_frame = j;
                    }
                }

                target_frame = lru_frame;


                // เก็บ Page ที่ถูกแทนที่
                result.steps[i].replaced_page =
                    frames[target_frame].page;
            }


            // ------------------------------------
            // ใส่ Page ใหม่
            // ------------------------------------

            frames[target_frame].page =
                current_page;

            frames[target_frame].valid = 1;


            // บันทึกว่า Page นี้ถูกใช้ล่าสุด
            last_used[target_frame] = i;
        }


        // ====================================
        // Save Frame State
        // ====================================

        for (int j = 0; j < frame_count; j++)
        {
            if (frames[j].valid)
            {
                result.steps[i].frames[j] =
                    frames[j].page;
            }
            else
            {
                result.steps[i].frames[j] =
                    EMPTY_FRAME;
            }
        }
    }


    return result;
}

