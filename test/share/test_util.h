
#include <stdint.h>

#ifndef TEST_UTIL_H
#define TEST_UTIL_H


//! Sample the clock cycle counter (used for timing checks)
uint32_t test_util_rdcycle() {
    uint32_t tr;
    #if defined LIBSCARV_ARCH_RISCV
        asm volatile ("rdcycle %0":"=r"(tr));
    #elif defined LIBSCARV_ARCH_RISCV_XCRYPTO
        asm volatile ("rdcycle %0":"=r"(tr));
    #elif defined LIBSCARV_ARCH_GENERIC
        tr = 10;
    #else
        tr = 10;
    #endif
    return tr;
}

//! Sample the clock cycle counter (used for timing checks)
uint32_t test_util_rdinstret() {
    uint32_t tr;
    #if defined LIBSCARV_ARCH_RISCV
        asm volatile ("rdinstret %0":"=r"(tr));
    #elif defined LIBSCARV_ARCH_RISCV_XCRYPTO
        asm volatile ("rdinstret %0":"=r"(tr));
    #elif defined LIBSCARV_ARCH_GENERIC
        tr = 10;
    #else
        tr = 10;
    #endif
    return tr;
}

#endif
