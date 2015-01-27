
CC = g++

SRCDIR = src/
BUILDDIR = bin/
TESTDIR = test/

SRCS = $(wildcard ${SRCDIR}*.cpp)
SRCS += $(wildcard ${SRCDIR}vecmath/src/*.cpp)
TESTS = $(wildcard ${TESTDIR}*.cpp)
TESTS += $(wildcard ${TESTDIR}unit/*.cpp)
TESTS += $(filter-out ${SRCDIR}main.cpp,$(SRCS))

OBJS = $(SRCS:.cpp=.o)
TESTOBJS = $(TESTS:.cpp=.o)
PROGNAME = raytracer.o
PROG = ${BUILDDIR}${PROGNAME}
TESTPROG = ${BUILDDIR}test.o
CFLAGS = -O2 -Wall -Wextra
INCFLAGS = -I${SRCDIR}vecmath/include

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LINKFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

clean-test:
	rm -f ${TESTDIR}*.o  ${TESTDIR}unit/*.o

clean-src:
	rm -f *.bak ${SRCDIR}vecmath/src/*.o ${SRCDIR}*.o core.*

clean-bin:
	rm -f $(PROG)

clean-misc:
	rm -f *.bak core.*

clean: clean-src clean-test clean-misc clean-bin

$(TESTPROG): $(TESTOBJS)
	$(CC) $(CFLAGS) $(TESTOBJS) -o $@ $(LINKFLAGS)

test: $(TESTPROG) FORCE
	${TESTPROG} --durations yes

FORCE:

run: $(PROG)
	${PROG}

render: $(PROG)
	${TESTDIR}render.sh

docs: FORCE
	doxygen
