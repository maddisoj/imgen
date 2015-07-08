CC = g++
SRCDIR := src/imgen
BUILDDIR := build
TARGET := bin/imgen
CFLAGS := -std=c++11 -pedantic -Wall -Wextra \
    -Wno-variadic-macros -Wno-unused-variable \
    -fexceptions -g -I src/
SRC := $(shell find $(SRCDIR) -type f -name *.cpp)
OBJ := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRC:.cpp=.o))
LIB = -lpng -lformat -lboost_program_options

$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	rm -r "$(BUILDDIR)" "$(TARGET)"

.PHONY: clean
