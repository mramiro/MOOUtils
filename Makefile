#
# Makefile
#
# My first makefile :)
#
# Created on: 04/08/2014
#     Author: Miguel A. Ramiro <mike.longbow@gmail.com>

IDIR := ./include
CC := gcc
CFLAGS := -O3 -Wall -fmessage-length=0 -I$(IDIR)

LDFLAGS := -lm
SOURCES := delta.c epsilon.c gamma.c memalloc.c moutils.c
EXAMPLE := example.c
_HEADERS := $(SOURCES:.c=.h)
HEADERS := $(patsubst %,$(IDIR)/%,$(_HEADERS))
OBJECTS := $(SOURCES:.c=.o)

TARGET_EXAMPLE := example
TARGET_STATICLIB := libmooutils.a

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

all: $(TARGET_EXAMPLE)
	
$(TARGET_STATICLIB): $(OBJECTS)
	ar -r $@ $^
	
$(TARGET_EXAMPLE): $(EXAMPLE) $(TARGET_STATICLIB) 
	$(CC) -o $@ $< $(CFLAGS) -L./ -lmooutils $(LDFLAGS) 

.PHONY: clean

clean:
	rm -f $(OBJECTS) *~ $(IDIR)/*~ $(TARGET_EXAMPLE) $(TARGET_STATICLIB) 