CC=gcc
AR=ar

CFLAGS=-Wall -I.
LDFLAGS=-lc_link -L.

LINKSRCS=c_link.c
LINKOBJS=$(LINKSRCS:.c=.o)
LINKLIB=libc_link.a

AGENTSRCS=$(wildcard agents/*.c)
AGENTS=$(AGENTSRCS:.c=)

all: $(LINKSRCS) $(LINKLIB) $(AGENTS)
	
$(LINKLIB): $(LINKOBJS)
	$(AR) rcs $(LINKLIB) $(LINKOBJS)
	
$(AGENTS): $(AGENTSRCS) $(LINKLIB)
	@echo Building $@
	$(CC) $(CFLAGS) $(LDFLAGS) $@.c -o $@

.c.o: c_link.h
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY : clean
clean:
	rm $(LINKOBJS) $(LINKLIB) $(AGENTS)
