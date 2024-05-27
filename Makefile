OS := $(shell uname -s 2>/dev/null || echo Windows)

# Define commands and variables based on the operating system
ifeq ($(OS),Linux)
    INSTALL_DIR = /usr/local/bin
    MKDIR = mkdir -p
    COPY = cp
    RM = rm -f
    SEP = /
    CC = gcc
else ifeq ($(OS),Darwin)
    INSTALL_DIR = /usr/local/bin
    MKDIR = mkdir -p
    COPY = cp
    RM = rm -f
    SEP = /
    CC = gcc
else
    INSTALL_DIR = C:\\Scripts
    MKDIR = if not exist $(INSTALL_DIR) mkdir $(INSTALL_DIR)
    COPY = copy
    RM = del /Q
    SEP = \\
    CC = gcc
endif

exec = flm.out
sources = $(wildcard src/*.c)
objects = $(patsubst src/%.c, src/%.o, $(sources))
flags = -g

$(exec): $(objects)
	$(CC) $(objects) $(flags) -o $(exec)

src/%.o: src/%.c include/%.h
	$(CC) -c $(flags) $< -o $@

install:
	$(MAKE)
	$(MKDIR) $(INSTALL_DIR)
	$(COPY) $(exec) $(INSTALL_DIR)$(SEP)$(exec)

clean:
	$(RM) $(exec)
	$(RM) src$(SEP)*.o
