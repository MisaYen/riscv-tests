#=======================================================================
# Makefile for riscv-tests/isa
#-----------------------------------------------------------------------

XLEN ?= 64

src_dir := .

ifeq ($(XLEN),64)
include $(src_dir)/rv64ui/Makefrag
include $(src_dir)/rv64uc/Makefrag
include $(src_dir)/rv64um/Makefrag
include $(src_dir)/rv64ua/Makefrag
include $(src_dir)/rv64uf/Makefrag
include $(src_dir)/rv64ud/Makefrag
include $(src_dir)/rv64uzfh/Makefrag
include $(src_dir)/rv64uzba/Makefrag
include $(src_dir)/rv64uzbb/Makefrag
include $(src_dir)/rv64uzbc/Makefrag
include $(src_dir)/rv64uzbs/Makefrag
include $(src_dir)/rv64si/Makefrag
include $(src_dir)/rv64ssvnapot/Makefrag
include $(src_dir)/rv64mi/Makefrag
include $(src_dir)/rv64mzicbo/Makefrag
endif
include $(src_dir)/rv32ui/Makefrag
include $(src_dir)/rv32uc/Makefrag
include $(src_dir)/rv32um/Makefrag
include $(src_dir)/rv32ua/Makefrag
include $(src_dir)/rv32uf/Makefrag
include $(src_dir)/rv32ud/Makefrag
include $(src_dir)/rv32uzfh/Makefrag
include $(src_dir)/rv32uzba/Makefrag
include $(src_dir)/rv32uzbb/Makefrag
include $(src_dir)/rv32uzbc/Makefrag
include $(src_dir)/rv32uzbs/Makefrag
include $(src_dir)/rv32si/Makefrag
include $(src_dir)/rv32mi/Makefrag

default: all

#--------------------------------------------------------------------
# Build rules
#--------------------------------------------------------------------

RISCV_PREFIX ?= riscv$(XLEN)-unknown-elf-
RISCV_GCC ?= $(RISCV_PREFIX)gcc
RISCV_GCC_OPTS ?= -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles
# RISCV_GCC_OPTS ?= -static -mcmodel=medany -nostdlib -nostartfiles
RISCV_OBJDUMP ?= $(RISCV_PREFIX)objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data
# RISCV_OBJDUMP ?= $(RISCV_PREFIX)objdump -D
RISCV_OBJDUMP_HUMAN ?= $(RISCV_PREFIX)objdump -S -M no-aliases -M numeric
RISCV_SIM ?= spike
RISCV_OBJCOPY ?= $(RISCV_PREFIX)objcopy -O binary
# OCFLAGS ?= --only-section=.text.init --only-section=.tohost --only-section=.riscv.attributes
# OCFLAGS ?= --only-section=.text.init --only-section=.text --only-section=.tohost --only-section=.data --only-section=.bss --only-section=.riscv.attributes

vpath %.S $(src_dir)

#------------------------------------------------------------
# Build assembly tests

%.dump: %
	$(RISCV_OBJDUMP) $< > $@

%.dump.human: %
	$(RISCV_OBJDUMP_HUMAN) $< > $@

%.bin: %
	$(RISCV_OBJCOPY) $< $@

%.text.bin: %
	$(RISCV_OBJCOPY) --only-section=.text $< $@

%.data.bin: %
	$(RISCV_OBJCOPY) --only-section=.data $< $@

%.mem: %.bin
	../create_mem.sh $<

%.text.mem: %.text.bin
	../create_mem.sh $<

%.data.mem: %.data.bin
	../create_mem.sh $<

%.out: %
	$(RISCV_SIM) --isa=rv64gc_zfh_zicboz_svnapot_zicntr_zba_zbb_zbc_zbs --misaligned $< 2> $@

%.out32: %
	$(RISCV_SIM) --isa=rv32gc_zfh_zicboz_svnapot_zicntr_zba_zbb_zbc_zbs --misaligned $< 2> $@

define compile_template

$$($(1)_p_tests): $(1)-p-%: $(1)/%.S
	$$(RISCV_GCC) $(2) $$(RISCV_GCC_OPTS) -I$(src_dir)/../my_env/p -I$(src_dir)/macros/scalar -T$(src_dir)/../link_p.ld $$< -o $$@
$(1)_tests += $$($(1)_p_tests)

$$($(1)_v_tests): $(1)-v-%: $(1)/%.S
	$$(RISCV_GCC) $(2) $$(RISCV_GCC_OPTS) -DENTROPY=0x$$(shell echo \$$@ | md5sum | cut -c 1-7) -std=gnu99 -O2 -I$(src_dir)/../my_env/v -I$(src_dir)/macros/scalar -T$(src_dir)/../link.ld $(src_dir)/../my_env/v/entry.S $(src_dir)/../my_env/v/*.c $$< -o $$@
$(1)_tests += $$($(1)_v_tests)

$(1)_tests_dump = $$(addsuffix .dump, $$($(1)_tests))

$(1): $$($(1)_tests_dump)

.PHONY: $(1)

COMPILER_SUPPORTS_$(1) := $$(shell $$(RISCV_GCC) $(2) -c -x c /dev/null -o /dev/null 2> /dev/null; echo $$$$?)

ifeq ($$(COMPILER_SUPPORTS_$(1)),0)
tests += $$($(1)_tests)
endif

endef

# march=rv32im
$(eval $(call compile_template,rv32ui,-march=rv32g -mabi=ilp32))
$(eval $(call compile_template,rv32uc,-march=rv32g -mabi=ilp32))
$(eval $(call compile_template,rv32um,-march=rv32g -mabi=ilp32))
$(eval $(call compile_template,rv32ua,-march=rv32g -mabi=ilp32))
$(eval $(call compile_template,rv32uf,-march=rv32g -mabi=ilp32))
$(eval $(call compile_template,rv32ud,-march=rv32g -mabi=ilp32))
$(eval $(call compile_template,rv32uzfh,-march=rv32g_zfh -mabi=ilp32))
$(eval $(call compile_template,rv32uzba,-march=rv32g_zba -mabi=ilp32))
$(eval $(call compile_template,rv32uzbb,-march=rv32g_zbb -mabi=ilp32))
$(eval $(call compile_template,rv32uzbc,-march=rv32g_zbc -mabi=ilp32))
$(eval $(call compile_template,rv32uzbs,-march=rv32g_zbs -mabi=ilp32))
$(eval $(call compile_template,rv32si,-march=rv32g -mabi=ilp32))
$(eval $(call compile_template,rv32mi,-march=rv32g -mabi=ilp32))
ifeq ($(XLEN),64)
$(eval $(call compile_template,rv64ui,-march=rv64g -mabi=lp64))
$(eval $(call compile_template,rv64uc,-march=rv64g -mabi=lp64))
$(eval $(call compile_template,rv64um,-march=rv64g -mabi=lp64))
$(eval $(call compile_template,rv64ua,-march=rv64g -mabi=lp64))
$(eval $(call compile_template,rv64uf,-march=rv64g -mabi=lp64))
$(eval $(call compile_template,rv64ud,-march=rv64g -mabi=lp64))
$(eval $(call compile_template,rv64uzfh,-march=rv64g_zfh -mabi=lp64))
$(eval $(call compile_template,rv64uzba,-march=rv64g_zba -mabi=lp64))
$(eval $(call compile_template,rv64uzbb,-march=rv64g_zbb -mabi=lp64))
$(eval $(call compile_template,rv64uzbc,-march=rv64g_zbc -mabi=lp64))
$(eval $(call compile_template,rv64uzbs,-march=rv64g_zbs -mabi=lp64))
$(eval $(call compile_template,rv64mzicbo,-march=rv64g_zicboz -mabi=lp64))
$(eval $(call compile_template,rv64si,-march=rv64g -mabi=lp64))
$(eval $(call compile_template,rv64ssvnapot,-march=rv64g -mabi=lp64))
$(eval $(call compile_template,rv64mi,-march=rv64g -mabi=lp64))
endif

tests_dump = $(addsuffix .dump, $(tests))
tests_dump_human = $(addsuffix .dump.human, $(tests))
tests_bin  = $(addsuffix .bin, $(tests))
tests_text_bin  = $(addsuffix .text.bin, $(tests))
tests_data_bin  = $(addsuffix .data.bin, $(tests))
tests_mem  = $(addsuffix .mem, $(tests))
tests_text_mem  = $(addsuffix .text.mem, $(tests))
tests_data_mem  = $(addsuffix .data.mem, $(tests))
tests_hex = $(addsuffix .hex, $(tests))
tests_out = $(addsuffix .out, $(filter rv64%,$(tests)))
tests32_out = $(addsuffix .out32, $(filter rv32%,$(tests)))

run: $(tests_out) $(tests32_out)

junk += $(tests) $(tests_dump) $(tests_dump_human) $(tests_bin) $(tests_text_bin) $(tests_data_bin) $(tests_mem) $(tests_text_mem) $(tests_data_mem) $(tests_hex) $(tests_out) $(tests32_out)

#------------------------------------------------------------
# Default

all: $(tests_dump) $(tests_dump_human) $(tests_bin)  $(tests_text_bin) $(tests_data_bin) $(tests_mem) $(tests_text_mem) $(tests_data_mem)

#------------------------------------------------------------
# Clean up

clean:
	rm -rf $(junk)
