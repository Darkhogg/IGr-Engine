# Original SDL-GL-basic Makefile template written by Hans de Ruiter
# Modified by Chris Brenton
#
# License:
# This source code can be used and/or modified without restrictions.
# It is provided as is and the author disclaims all warranties, expressed
# or implied, including, without limitation, the warranties of
# merchantability and of fitness for any purpose. The user must assume the
# entire risk of using the Software.

CC     = g++ -std=c++11
#CC     = gfilt /cand:L -m32
CP     = cp
RM     = rm -rf
KILL   = killall -9
SHELL  = /bin/bash
MAKE   = make
TIME   = time

IFLAGS    =
LFLAGS    =
DEBUG     = -ggdb
OPTIMIZE  =
ERROR     = -Wconversion -Werror
CFLAGS    = $(OPTIMIZE) -Wall -c $(DEBUG) $(ERROR) $(IFLAGS)
LDFLAGS   = $(OPTIMIZE) $(DEBUG) $(ERROR) $(LFLAGS)

#TARGET = boiler
ARGS   =

# Additional linker libraries
LIBS = $(LIBFLAGS)
FRAMEWORKS = -framework OpenGL -framework sfml -framework sfml-window -framework sfml-graphics -framework sfml-system

# -------------------------------------------------------------

# The source files
SRCS = $(wildcard ./*.cpp ./*/*.cpp)

OBJS = $(SRCS:.cpp=.o)

# Rules for building
all: $(OBJS)
#	$(CC) $(FRAMEWORKS) $(OBJS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: lib
lib:
	$(shell) ./lib.sh

run:
	./$(TARGET) $(ARGS)

gdb:
	gdb --args ./$(TARGET) $(ARGS)

vg:   valgrind

valgrind:
	valgrind --tool=memcheck --leak-check=full ./$(TARGET) $(ARGS)

clean:
	$(RM) $(TARGET) $(OBJS)

killall:
	$(KILL) $(TARGET)
