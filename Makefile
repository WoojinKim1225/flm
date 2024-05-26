OS := $(shell uname -s 2>/dev/null || echo Windows)

# Define commands and variables based on the operating system
ifeq ($(OS),Linux)
    INSTALL_DIR = /usr/local/bin
    MKDIR = mkdir -p
    COPY = cp
    RM = rm -f
    SEP = /
else ifeq ($(OS),Darwin)
    INSTALL_DIR = /usr/local/bin
    MKDIR = mkdir -p
    COPY = cp
    RM = rm -f
    SEP = /
else
    INSTALL_DIR = C:\\Scripts
    MKDIR = if not exist $(INSTALL_DIR) mkdir $(INSTALL_DIR)
    COPY = copy
    RM = del /Q
    SEP = \\
endif

exec = flm.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	$(MAKE)
	$(MKDIR) $(INSTALL_DIR)
	$(COPY) flm.out $(INSTALL_DIR)$(SEP)flm.out


clean:
	$(RM) *.out
	$(RM) *.o
	$(RM) src$(SEP)*.o
