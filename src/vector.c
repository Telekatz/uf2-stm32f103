/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2010 Piotr Esden-Tempski <piotr@esden.net>,
 * Copyright (C) 2012 chrysn <chrysn@fsfe.org>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/vector.h>

/* load optional platform dependent initialization routines */

/* Symbols exported by the linker script(s): */
//extern unsigned _data_loadaddr, _data, _edata, _ebss, _stack;
typedef void (*funcp_t) (void);
extern funcp_t __preinit_array_start, __preinit_array_end;
extern funcp_t __init_array_start, __init_array_end;
extern funcp_t __fini_array_start, __fini_array_end;

void main(void);
void blocking_handler(void);
void null_handler(void);

typedef struct {
  unsigned int *initial_sp_value; /**< Initial stack pointer value. */
  vector_table_entry_t reset;
  vector_table_entry_t nmi;
  vector_table_entry_t hard_fault;
  vector_table_entry_t memory_manage_fault; /* not in CM0 */
  vector_table_entry_t bus_fault;           /* not in CM0 */
  vector_table_entry_t usage_fault;         /* not in CM0 */
  vector_table_entry_t reserved_x001c[4];
  vector_table_entry_t sv_call;
  vector_table_entry_t debug_monitor;       /* not in CM0 */
  vector_table_entry_t reserved_x0034;
  vector_table_entry_t pend_sv;
  vector_table_entry_t systick;
} vector_table2_t;

__attribute__ ((section(".vectors")))
vector_table2_t vector_table2 = {
	.initial_sp_value = &_stack,
	.reset = reset_handler,
	.nmi = nmi_handler,
	.hard_fault = hard_fault_handler,
	.sv_call = sv_call_handler,
	.pend_sv = pend_sv_handler,
	.systick = sys_tick_handler,
};



