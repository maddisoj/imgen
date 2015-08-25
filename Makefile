CC = g++
SRCDIR := src/imgen
PYSETUP := src/bindings/setup.py
BUILDDIR := build
MODULEDIR := python
TARGET := imgen
SRC := $(shell find $(SRCDIR) -type f -name *.cpp)
OBJ := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRC:.cpp=.o))
CFLAGS := -std=c++11 -pedantic -Wall -Wextra -Wno-variadic-macros\
	  -Wno-unused-variable -fexceptions -g -O3 -Isrc/\
	  $(shell python3-config --cflags) $(shell pkg-config --cflags cairo)
LIBS := -lpng -lformat -lboost_python3 -lboost_program_options -lboost_system\
        -lboost_filesystem\
        $(shell python3-config --ldflags) $(shell pkg-config --libs cairo)

$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $^ -o $(TARGET) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

bindings:
	@python $(PYSETUP) build
	@python $(PYSETUP) install --install-lib $(MODULEDIR)

clean:
	rm -rf "$(BUILDDIR)" "$(TARGET)" "$(MODULEDIR)"

.PHONY: bindings bindings-install clean
