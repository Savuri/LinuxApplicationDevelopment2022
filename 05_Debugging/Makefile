CC = cc
CFLAGS = -Wall -Werror -Wextra -O3 -fPIC
DEBUG_CFLAGS = -Wall -Werror -O0 -g
GENERATES = range-debug range test/script1.result test/script2.result

test: range-debug scripts/script1.gdb scripts/script2.gdb test/script1.expected test/script2.expected Makefile
	gdb -x scripts/script1.gdb --args range-debug 1 12 | grep "@@@*" | cat > ./test/script1.result
	gdb -x scripts/script2.gdb --args range-debug -100 100 3 | grep "@@@*" | cat > ./test/script2.result
	cmp test/script1.expected test/script1.result
	cmp test/script2.expected test/script2.result
	@ echo "Test ok"

range: range.c

range-debug: range.c
	$(CC) $(DEBUG_CFLAGS) range.c -o range-debug

clean:
	rm -f $(GENERATES)