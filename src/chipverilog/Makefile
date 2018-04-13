######################################################################
#
# DESCRIPTION: Verilator Example: Small Makefile
#
# This calls the object directory makefile.  That allows the objects to
# be placed in the "current directory" which simplifies the Makefile.
#
# Copyright 2003-2018 by Wilson Snyder. This program is free software; you can
# redistribute it and/or modify it under the terms of either the GNU
# Lesser General Public License Version 3 or the Perl Artistic License
# Version 2.0.
#
######################################################################
# Check for sanity to avoid later confusion

ifneq ($(words $(CURDIR)),1)
 $(error Unsupported: GNU Make cannot build in directories containing spaces, build elsewhere: '$(CURDIR)')
endif

######################################################################

# This is intended to be a minimal example.  Before copying this to start a
# real project, it is better to start with a more complete example,
# e.g. examples/tracing_c.

# If $VERILATOR_ROOT isn't in the environment, we assume it is part of a
# package inatall, and verilator is in your path. Otherwise find the
# binary relative to $VERILATOR_ROOT (such as when inside the git sources).
ifeq ($(VERILATOR_ROOT),)
VERILATOR = verilator
else
export VERILATOR_ROOT
VERILATOR = $(VERILATOR_ROOT)/bin/verilator
endif

verilog-v-src = \
andverilog.v \
orverilog.v \
twolatchverilog.v \
latchverilog.v \
ffverilog.v

verilog-obj = $(verilog-v-src:.v=.o)

all: $(verilog-obj) verilated.o

$(verilog-obj):
	$(VERILATOR) --Mdir obj_$(@:.o=) -CFLAGS "-I../../ -I../../include" -cc $(@:.o=.v) -cc $(@:.o=.cpp)
	$(MAKE) -C obj_$(@:.o=) -f V$(@:.o=.mk)
	$(MAKE) -C obj_$(@:.o=) -f V$(@:.o=.mk) $@
	cp obj_$(@:.o=)/V$(@:.o=)__ALL.a ./
	cp obj_$(@:.o=)/$@ ./
	echo $(@:.o=)

verilated.o:
	g++  -I.  -MMD -I/usr/share/verilator/include -I/usr/share/verilator/include/vltstd -DVL_PRINTF=printf -DVM_COVERAGE=0 -DVM_SC=0 -DVM_TRACE=0 -faligned-new -Wno-bool-operation -Wno-sign-compare -Wno-uninitialized -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-shadow     -I../../ -I../../include   -c -o verilated.o /usr/share/verilator/include/verilated.cpp

######################################################################

maintainer-copy::
clean mostlyclean distclean maintainer-clean::
	-rm -rf obj_* *.log *.dmp *.vpd core *ALL.a $(verilog-obj) verilated.*
