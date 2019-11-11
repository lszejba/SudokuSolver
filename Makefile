CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

SRCS=board.cpp main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: solver

solver: $(OBJS)
	$(CXX) $(LDFLAGS) -o solver $(OBJS) $(LDLIBS)

board.o: board.cpp board.hpp

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) solver

