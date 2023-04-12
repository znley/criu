#ifndef __CR_IRMAP__H__
#define __CR_IRMAP__H__
char *irmap_lookup(unsigned int s_dev, unsigned long i_ino);
struct FhEntry;
int irmap_queue_cache(unsigned int dev, unsigned long ino,
		struct FhEntry *fh);
int irmap_predump_prep(void);
int irmap_predump_run(void);
int check_open_handle(unsigned int s_dev, unsigned long i_ino,
		struct FhEntry *f_handle);
int irmap_load_cache(void);
int irmap_scan_path_add(char *path);
#endif
