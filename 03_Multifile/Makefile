GENERATES = prog prog-a prog-so prog.so liboutput.so
TRASH = *.o *~ o.* test_file_* *.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -O3 -fPIC
DYN = -shared
LIB_PATH=$(PWD)


all:	prog prog-a prog-so

prog:	const.o fun.o prog.o

prog-a: prog.o liboutput.a
	$(CC) $(CFLAGS) $^ -o $@

liboutput.a: fun.o const.o
	ar -rcs $@ $^

prog-so: prog.o liboutput.so
	$(CC) $(CFLAGS) $^ -o $@

liboutput.so: fun.o const.o
	$(CC) $(CFLAGS) $(DYN) $^ -o $@

fun.o:  outlib.h

clean:
	rm -f $(TRASH)
	rm -rf $(GENERATES)

test: verify_tests all
	@ echo
	@ echo tests passed

verify_tests: run_tests
	cmp test_file_0 test_file_0-a
	cmp test_file_0 test_file_0-so
	cmp test_file_1 test_file_1-a
	cmp test_file_1 test_file_1-so
	cmp test_file_2 test_file_2-a
	cmp test_file_2 test_file_2-so


run_tests: prog prog-a prog-so
	./prog > test_file_0 2>&1
	./prog text1 > test_file_1 2>&1
	./prog text1 text2 text3 > test_file_2 2>&1
	./prog-a > test_file_0-a 2>&1
	./prog-a text1 > test_file_1-a 2>&1
	./prog-a text1 text2 text3 > test_file_2-a 2>&1
	LD_LIBRARY_PATH=$(LIB_PATH) ./prog-so > test_file_0-so 2>&1
	LD_LIBRARY_PATH=$(LIB_PATH) ./prog-so text1 > test_file_1-so 2>&1
	LD_LIBRARY_PATH=$(LIB_PATH) ./prog-so text1 text2 text3 > test_file_2-so 2>&1
