#ifndef COMPEL_ARCH_SYSCALL_TYPES_H__
#define COMPEL_ARCH_SYSCALL_TYPES_H__

#include <common/asm/bitsperlong.h>
/* Types for sigaction, sigprocmask syscalls */
typedef void rt_signalfn_t(int, siginfo_t *, void *);
typedef rt_signalfn_t *rt_sighandler_t;

typedef void rt_restorefn_t(void);
typedef rt_restorefn_t *rt_sigrestore_t;

//TODO upstream NSIG is 64
/** refer to arch/loongarch/include/uapi/asm/signal.h*/
#define _KNSIG	64
#define _NSIG_BPW BITS_PER_LONG
#define _KNSIG_WORDS (_KNSIG / _NSIG_BPW)

/*
 * Note: as k_rtsigset_t is the same size for 32-bit and 64-bit,
 * sig defined as uint64_t rather than (unsigned long) - for the
 * purpose if we ever going to support native 32-bit compilation.
 */

typedef struct {
	uint64_t sig[_KNSIG_WORDS];
} k_rtsigset_t;

typedef struct {
	rt_sighandler_t rt_sa_handler;
	unsigned long rt_sa_flags;
	rt_sigrestore_t rt_sa_restorer;
	k_rtsigset_t rt_sa_mask;
} rt_sigaction_t;

#define SA_RESTORER 0x04000000

#endif /* COMPEL_ARCH_SYSCALL_TYPES_H__ */
