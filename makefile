CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

all: bin/mps
	@echo -n ""

bin/mps: src/main.cpp
	$(CC) $(OPTFLAGS) $< -o bin/mps

dbg: bin/mps_dbg
	@echo -n ""

bin/mps_dbg: src/main.cpp
	$(CC) $(DBGFLAGS) $< -o bin/mps_dbg

clean:
	rm -rf bin/*
