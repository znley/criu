#include <unistd.h>

#include "restorer.h"
#include "asm/restorer.h"
#include <compel/asm/fpu.h>

#include <compel/plugins/std/syscall.h>
#include "log.h"
#include "cpu.h"

int restore_nonsigframe_gpregs(UserLoongarch64GpregsEntry *r)
{
	return 0;
}

#define SHMLBA 0x00010000
unsigned long arch_shmat(int shmid, void *shmaddr, int shmflg, unsigned long size)
{
	unsigned long smap;

	/* SHMLBA-aligned, direct call shmat() */
	if (!((unsigned long)shmaddr & (SHMLBA - 1)))
		return sys_shmat(shmid, shmaddr, shmflg);

	smap = sys_shmat(shmid, NULL, shmflg);
	if (IS_ERR_VALUE(smap)) {
		pr_err("shmat() with NULL shmaddr failed: %d\n", (int)smap);
		return smap;
	}

	/* We're lucky! */
	if (smap == (unsigned long)shmaddr)
		return smap;

	/* Warn ALOUD */
	pr_warn("Restoring shmem %p unaligned to SHMLBA.\n", shmaddr);

	smap = sys_mremap(smap, size, size, MREMAP_FIXED | MREMAP_MAYMOVE, (unsigned long)shmaddr);
	if (IS_ERR_VALUE(smap))
		pr_err("mremap() for shmem failed: %d\n", (int)smap);
	return smap;
}
