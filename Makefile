# Original SDL-GL-basic Makefile template written by Hans de Ruiter
# Modified by Chris Brenton
#
# License:
# This source code can be used and/or modified without restrictions.
# It is provided as is and the author disclaims all warranties, expressed
# or implied, including, without limitation, the warranties of
# merchantability and of fitness for any purpose. The user must assume the
# entire risk of using the Software.
CC     = g++ -std=c++11 -fdiagnostics-color -pedantic

CCACHE_EXISTS := $(shell ccache -V)
ifdef CCACHE_EXISTS
  CC := ccache $(CC)
endif

#CC     = gfilt /cand:L -m32
CP     = cp
BTOC   = ./blob-to-hpp
RM     = rm -rf
KILL   = killall -9
SHELL  = /bin/bash
MAKE   = make --no-print-directory
TIME   = time
JOBS   = $(shell nproc)

IFLAGS    =
LFLAGS    =
DEBUG     = -ggdb
OPTIMIZE  = -O3 -funroll-loops
#ERROR     = -Wconversion -Werror
CFLAGS    = $(OPTIMIZE) -Wall -c $(DEBUG) $(ERROR) $(IFLAGS)
LDFLAGS   = $(OPTIMIZE) $(DEBUG) $(ERROR) $(LFLAGS)

TARGET = engine
ARGS   =

# Additional linker libraries
LIBS = $(LIBFLAGS)
FRAMEWORKS = -lGL -lGLU -lsfml-window -lsfml-graphics -lsfml-system

# Modify makeflags
MAKEFLAGS+=-j$(JOBS)

# -------------------------------------------------------------

# The source files
SRCS = $(wildcard ./*.cpp ./*/*.cpp)
BLOBS = $(wildcard ./*.blob ./*/*.blob)

OBJS = $(SRCS:.cpp=.o)
HBLOBS = $(BLOBS:.blob=.blob.hpp)

# Rules for building
all: $(TARGET)

$(TARGET): $(HBLOBS) $(OBJS)
	#$(CC) $(FRAMEWORKS) $(OBJS) $(LDFLAGS) -o $@

%.blob.hpp: %.blob
	$(BTOC) $<

%.o: %.cpp $(HBLOBS)
	$(CC) $(CFLAGS) $< -o $@


.PHONY: lib
lib:
	$(shell) ./lib.sh

run: $(TARGET)
	./$(TARGET) $(ARGS)

gdb:
	gdb --args ./$(TARGET) $(ARGS)

vg:   valgrind

valgrind:
	valgrind --tool=memcheck --leak-check=full ./$(TARGET) $(ARGS)

clean:
	$(RM) $(TARGET) $(OBJS)

ultraclean: clean
	$(RM) $(HBLOBS)

killall:
	$(KILL) $(TARGET)

full:
	$(MAKE) clean
	$(MAKE) run