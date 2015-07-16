CC = g++
SRCDIR := src/imgen
PYSETUP := src/bindings/setup.py
BUILDDIR := build
TARGET := imgen
SRC := $(shell find $(SRCDIR) -type f -name *.cpp)
OBJ := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRC:.cpp=.o))
CFLAGS := -std=c++11 -pedantic -Wall -Wextra -Wno-variadic-macros\
	  -Wno-unused-variable -fexceptions -g -Isrc/\
	  $(shell python3-config --cflags) $(shell pkg-config --cflags cairo)
LIBS := -lpng -lformat -lboost_python3 -lboost_program_options -lboost_system\
        -lboost_filesystem\
        $(shell python3-config --ldflags) $(shell pkg-config --libs cairo)

$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $^ -o $(TARGET) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

bindings:
	@python $(PYSETUP) build

bindings-install: bindings
	@sudo python $(PYSETUP) install

clean:
	rm -r "$(BUILDDIR)" "$(TARGET)" &> /dev/null

.PHONY: bindings bindings-install clean
