CXX = g++

PROJECT = raytracer

SRCDIR = src
BINDIR = bin
# LIBDIR = lib
INCDIR = include

SOURCES =  $(SRCDIR)/*.cpp 
EXECUTABLE = $(BINDIR)/$(PROJECT)


CFLAGS = -std=c++17 -Wall -g

IFLAGS = -I$(INCDIR) 
# LDFLAGS = -L$(LIBDIR)

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(IFLAGS) $(LDFLAGS)


.PHONY: clean
clean:
	rm -f $(BINDIR)/*
