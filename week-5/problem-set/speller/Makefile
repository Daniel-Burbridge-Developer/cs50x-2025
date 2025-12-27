speller: speller.o dictionary.o
	cc -ggdb3 -gdwarf-4 -O0  -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -o speller speller.o dictionary.o -lm

speller.o: speller.c dictionary.h
	cc -ggdb3 -gdwarf-4 -O0  -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o speller.o speller.c

dictionary.o: dictionary.c dictionary.h
	cc -ggdb3 -gdwarf-4 -O0  -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o dictionary.o dictionary.c
