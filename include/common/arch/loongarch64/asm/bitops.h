#ifndef _LINUX_BITOPS_H
#define _LINUX_BITOPS_H
#include "common/asm-generic/bitops.h"

/**
 * test_and_set_bit - Set a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */

#if (BITS_PER_LONG == 32)
#define AMOR_SYNC "amor_db.w"
#elif (BITS_PER_LONG == 64)
#define AMOR_SYNC "amor_db.d"
#else
#error "Unexpected BITS_PER_LONG"
#endif

#define BIT_MASK(nr) (1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr) (1UL << ((nr) / BITS_PER_LONG))
static inline int test_and_set_bit(unsigned long nr, volatile unsigned long *addr)
{
    unsigned long res, mask;
    mask = BIT_MASK(nr);
    asm volatile(
             AMOR_SYNC " %0, %2, %1"
            : "=&r"(res), "+ZB"(addr[BIT_WORD(nr)])
            : "r"(mask)
            : "memory"
            );
    return (res & mask) != 0;
}

#endif
