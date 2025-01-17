CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g $(shell root-config --cflags) -Wall
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

SRCS=object.cpp field.cpp group.cpp logicallane.cpp board.cpp main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: solver

solver: $(OBJS)
	$(CXX) $(LDFLAGS) -o solver $(OBJS) $(LDLIBS)

object.o: object.cpp object.hpp

field.o: field.cpp field.hpp

group.o: group.cpp group.hpp

board.o: board.cpp board.hpp

logicallane.o: logicallane.cpp logicallane.hpp

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) solver

