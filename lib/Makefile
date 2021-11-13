#
# List data structure makefile
#
# Important! Dependencies are done automatically by 'make dep', which also
# removes any old dependencies. Do not modify it...
#
# 2021, d3phys
#

OBJS  = logs.o

lib.o: $(OBJS) subdirs
	$(LD) -r -o $@ $(OBJS)

include $(TOPDIR)/Rules.makefile

### Dependencies ###
logs.o: logs.cpp /home/d3phys/Code/akinator/include/logs.h
