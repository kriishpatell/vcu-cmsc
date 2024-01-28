## !!!!!!!!!!!
## !!! Cannot reliably use gprof/gcov on executables compiled by clang
## !!! (with optimization) on CLEAR S19 software stack
## !!!
## !!!!!!!!!!!

## CC       = clang
CC       = gcc
OPT      = 3
PERF_STACK = 6

CFLAGS   = -Wall -g

PROGRAMS = sample-nonopt sample-opt sample-gprof-nonopt sample-gprof-opt sample-gcov

.PHONY: all all-profiling perf-out

all: $(PROGRAMS)

perf-out: perf-nonopt.out perf-opt.out

all-profiling: gmon-nonopt.out gmon-opt.out sample.c.gcov perf-out


sample-nonopt: sample.c
	$(CC) $(CFLAGS) -o sample-nonopt sample.c

sample-opt: sample.c
	$(CC) -O$(OPT) $(CFLAGS) -o sample-opt sample.c

sample-gprof-nonopt: sample.c
	$(CC) $(CFLAGS) -pg -o sample-gprof-nonopt sample.c

sample-gprof-opt: sample.c
	$(CC) -O$(OPT) $(CFLAGS) -pg -o sample-gprof-opt sample.c

gmon-nonopt.out: sample-gprof-nonopt testinput
	./sample-gprof-nonopt < testinput
	gprof sample-gprof-nonopt > gmon-nonopt.out

gmon-opt.out: sample-gprof-opt testinput
	./sample-gprof-opt < testinput
	gprof sample-gprof-opt > gmon-opt.out

perf-opt.out: sample-opt
	perf record -e cycles:u --call-graph dwarf ./$< < testinput
	perf report -s sym,srcline --stdio --max-stack $(PERF_STACK) > $@

perf-nonopt.out: sample-nonopt
	perf record -e cycles:u --call-graph dwarf ./$< < testinput
	perf report -s sym,srcline --stdio --max-stack $(PERF_STACK) > $@

sample-gcov: sample.c
	$(CC) -fprofile-arcs -ftest-coverage -o sample-gcov sample.c

sample.c.gcov: sample-gcov
	./sample-gcov < testinput
	gcov sample.c

clean:
	$(RM) -f $(PROGRAMS) *.out *.gcov *.gcno *.gcda core.* perf.data*
