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

#ifndef _JAILHOUSE_MMIO_H
#define _JAILHOUSE_MMIO_H

#include <jailhouse/paging.h>
#include <asm/percpu.h>

struct mmio_access {
	unsigned int inst_len;
	unsigned int size;
	unsigned int reg;
};

static inline u32 mmio_read32(void *address)
{
	return *(volatile u32 *)address;
}

static inline u64 mmio_read64(void *address)
{
	return *(volatile u64 *)address;
}

static inline void mmio_write32(void *address, u32 value)
{
	*(volatile u32 *)address = value;
}

static inline void mmio_write64(void *address, u64 value)
{
	*(volatile u64 *)address = value;
}

struct mmio_access mmio_parse(struct per_cpu *cpu_data, unsigned long pc,
			      const struct guest_paging_structures *pg_structs,
			      bool is_write);

/**
 * mmio_read32_field() - Read value of 32-bit register field
 * @addr:	Register address.
 * @mask:	Bit mask. Shifted value must be provided which describes both
 * 		starting bit position (1st non-zero bit) and length of the field.
 *
 * Return: Field value of register.
 */
static inline u32 mmio_read32_field(void *addr, u32 mask)
{
	return (mmio_read32(addr) & mask) >> (__builtin_ffs(mask) - 1);
}

/**
 * mmio_write32_field() - Write value of 32-bit register field
 * @addr:	Register address.
 * @mask:	Bit mask. See mmio_read32_field() for more details.
 * @value:	Register field value (must be the same length as mask).
 *
 * Update field value of 32-bit register, leaving all other fields unmodified.

 * Return: None.
 */
static inline void mmio_write32_field(void *addr, u32 mask, u32 value)
{
	mmio_write32(addr, (mmio_read32(addr) & ~mask) |
			((value << (__builtin_ffs(mask) - 1)) & mask));
}

/**
 * mmio_read64_field() - Read value of 64-bit register field.
 * See mmio_read32_field() for more details.
 */
static inline u64 mmio_read64_field(void *addr, u64 mask)
{
	return (mmio_read64(addr) & mask) >> (__builtin_ffsl(mask) - 1);
}

/**
 * mmio_write64_field() - Write value of 64-bit register field.
 * See mmio_write32_field() for more details.
 */
static inline void mmio_write64_field(void *addr, u64 mask, u64 value)
{
	mmio_write64(addr, (mmio_read64(addr) & ~mask) |
			((value << (__builtin_ffsl(mask) - 1)) & mask));
}

#endif /* !_JAILHOUSE_MMIO_H */
