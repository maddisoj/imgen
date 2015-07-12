CC = g++
SRCDIR := src/imgen
BUILDDIR := build
TARGET := imgen
CFLAGS := -std=c++11 -pedantic -Wall -Wextra -Wno-variadic-macros \
	  -Wno-unused-variable -fexceptions -g -Isrc/
SRC := $(shell find $(SRCDIR) -type f -name *.cpp)
OBJ := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRC:.cpp=.o))
LIB = -lpng -lformat -lboost_python3 -lboost_program_options -lboost_system \
      -lboost_filesystem

$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $^ -o $(TARGET) $(LIB) $(shell python3-config --ldflags)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(shell python3-config --cflags) $(INC) -c -o $@ $<

clean:
	rm -r "$(BUILDDIR)" "$(TARGET)"

.PHONY: clean
