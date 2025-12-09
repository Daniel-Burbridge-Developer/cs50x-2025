# The name of your program (without the .c extension)
# Change this to match your source file name
PROGRAM = hello
CC = cc

# Compiler flags
# -Wall: Enable all common warnings
# -Wextra: Enable extra warnings
# -Werror: Treat warnings as errors (helps catch bugs early)
# -pedantic: Strict ISO C compliance
# -std=c11: Use C11 standard
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11

# Libraries to link against
# -lcs50: Link with the CS50 library
LIBS = -lcs50

all: $(PROGRAM)
$(PROGRAM): $(PROGRAM).c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

# Run "make clean" to remove the executable
clean:
	rm -f $(PROGRAM)

# Phony targets: these don't create files with these names
.PHONY: all clean

