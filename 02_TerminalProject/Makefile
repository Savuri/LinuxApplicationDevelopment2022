LDLIBS=-lncurses
#CFLAGS=-Wall -Wshadow -Werror -Wextra -g
OPTLEVEL=-O3
COMPILER=gcc

show: show.c
	@${COMPILER} $(CFLAGS) ${OPTLEVEL} show.c $(LDLIBS) -o show
clean:
	@rm -rf show