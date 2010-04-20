CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=c-link.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=rps-c

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
