#ifndef COMMON_H
#define COMMON_H

#define MAX_PAGES 100
#define MAX_FRAMES 20
#define MAX_REF 100

#define EMPTY_FRAME -1

typedef struct {
    int page;
    int valid;
} Frame;

/* สถานะของ Page Replacement ในแต่ละ Step */
typedef struct {
    int page;                       // page ที่กำลัง reference
    int frames[MAX_FRAMES];         // สถานะ frame หลังจากทำ step นี้
    int is_fault;                   // 1 = fault, 0 = hit
    int replaced_page;              // page ที่ถูกไล่ออก, -1 = ไม่มี
} SimStep;

/* ผลลัพธ์ทั้งหมดจากการรัน Algorithm หนึ่งครั้ง */
typedef struct {
    int faults;
    int hits;
    int total_refs;
    int num_frames;

    SimStep steps[MAX_REF];
} SimResult;

#endif