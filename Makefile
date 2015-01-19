CC = g++
SRCDIR = src/
BUILDDIR = bin/
SRCS = $(wildcard ${SRCDIR}*.cpp)
SRCS += $(wildcard ${SRCDIR}vecmath/src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
PROGNAME = raytracer.o
PROG = ${BUILDDIR}${PROGNAME}
CFLAGS = -O2 -Wall -Wextra
INCFLAGS = -I${SRCDIR}vecmath/include

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LINKFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

clean:
	rm -f *.bak ${SRCDIR}vecmath/src/*.o ${SRCDIR}*.o core.* $(PROG)

test: clean $(PROG)
	./test/run.sh
