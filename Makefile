CC = g++

PROJECT = raytracer

SRCDIR = src
BINDIR = bin
# LIBDIR = lib
INCDIR = include

SOURCES =  $(SRCDIR)/*.cpp
EXECUTABLE = $(BINDIR)/$(PROJECT)


CFLAGS = -g -std=c++17 -Wall

IFLAGS = -I$(INCDIR) -I$(INCDIR)/Eigen
# LDFLAGS = -L$(LIBDIR)

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^ $(IFLAGS) $(LDFLAGS)


.PHONY: clean
clean:
	rm -f $(BINDIR)/*
