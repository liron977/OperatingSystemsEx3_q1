# Makefile for ex3_q1 winter 2023A

CFLAGS   = -Wall -std=c99 -pthread
LDFLAGS  = -lm -pthread
CC       = gcc
ECHO     = @echo "going to build target $@ (dependent on $^)"

# the following is used to assign different values according to OS
# uname is a linux command (try it).
# commented out for now.
# OS := $(shell uname)
# ifneq (,$(findstring LINUX,$(OS)))
#   VAR =
# else
#   VAR =
# endif

PROG1 = ex3_q1 

all: $(PROG1) test

ex3_q1: ex3_q1.c ex3_q1.h ex3_q1_given.h ex3_q1_given.c
	$(ECHO)
	gcc ex3_q1.c ex3_q1_given.c $(CFLAGS) $(LDFLAGS) -o $@


clean:
	rm -vf *.o ${PROG1}

test: $(PROG1)
	@echo going to run test...
	./ex3_q1 gr_1.txt
	./ex3_q1 gr_1.txt gr_2.txt
	./ex3_q1 gr_1.txt gr_2.txt gr_3.txt