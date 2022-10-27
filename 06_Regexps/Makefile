CC = cc
CFLAGS = -Wall -Werror -Wextra -O3 -fPIC
GENERATES = esub

esub: esub.c

tests: esub
	./tests.sh

clean:
	rm -f $(GENERATES)