/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) Siemens AG, 2013
 *
 * Authors:
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include <linux/ioctl.h>
#include <linux/types.h>
#include <jailhouse/cell-config.h>

struct jailhouse_preload_image {
	__u64 source_address;
	__u64 size;
	__u64 target_address;
	__u64 padding;
};

struct jailhouse_cell_cfg {
	__u64 address;
	__u32 size;
};

struct jailhouse_cell_init {
	struct jailhouse_cell_cfg config;
	__u32 num_preload_images;
	struct jailhouse_preload_image image[];
};

#define JAILHOUSE_ENABLE		_IOW(0, 0, struct jailhouse_system)
#define JAILHOUSE_DISABLE		_IO(0, 1)
#define JAILHOUSE_CELL_CREATE		_IOW(0, 2, struct jailhouse_cell_init)
#define JAILHOUSE_CELL_DESTROY		_IOW(0, 4, struct jailhouse_cell_cfg)
