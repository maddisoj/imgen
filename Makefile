CC = g++
SRCDIR := src
BUILDDIR := build
TARGET := bin/wallgen

CFLAGS := -std=c++11 -pedantic -Wall -Wextra \
    -Wno-variadic-macros -Wno-unused-variable \
    -fexceptions
SRC := $(shell find $(SRCDIR) -type f -name *.cpp)
OBJ := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRC:.cpp=.o))
LIB = -lxcb

$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -r "$(BUILDDIR)" "$(TARGET)"

run:
	@./$(TARGET)

.PHONY: clean
