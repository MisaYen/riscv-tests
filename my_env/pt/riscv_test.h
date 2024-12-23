// See LICENSE for license details.

#ifndef _ENV_PHYSICAL_SINGLE_CORE_TIMER_H
#define _ENV_PHYSICAL_SINGLE_CORE_TIMER_H

#include "../p/riscv_test.h"

#define TIMER_INTERVAL 50

#undef EXTRA_INIT_TIMER
#define EXTRA_INIT_TIMER                                                \
        li a1, 0xF0004000;  /*load mtimecmp address*/                   \
        li a2, 0xF000BFF8;  /*load mtime address*/                      \
        li a0, MIP_MTIP;                                                \
        csrs mie, a0;                                                   \
        lw a0, 0(a2);       /*csrr a0, mtime;*/                         \
        addi a0, a0, TIMER_INTERVAL;                                    \
        sw a0, 0(a1);      /*csrw mtimecmp, a0;*/                       \

#if SSTATUS_XS != 0x18000
# error
#endif
#define XS_SHIFT 15

#undef INTERRUPT_HANDLER
#define INTERRUPT_HANDLER                                               \
        slli t5, t5, 1;                                                 \
        srli t5, t5, 1;                                                 \
        add t5, t5, -IRQ_M_TIMER;                                       \
        bnez t5, other_exception; /* other interrups shouldn't happen */\
        li t6, 0xF000BFF8;                                              \
        li t4, 0xF0004000;                                              \
        lw t5, 0(t6);             /*csrr t5, mtime;*/                   \
        addi t5, t5, TIMER_INTERVAL;                                    \
        sw t5, 0(t4);             /*csrw mtimecmp, t5;*/                \
        mret;                                                           \

//-----------------------------------------------------------------------
// Data Section Macro
//-----------------------------------------------------------------------

#undef EXTRA_DATA
#define EXTRA_DATA                                                      \
        .align 3;                                                       \
regspill:                                                               \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
        .dword 0xdeadbeefcafebabe;                                      \
evac:                                                                   \
        .skip 32768;                                                    \

#endif
