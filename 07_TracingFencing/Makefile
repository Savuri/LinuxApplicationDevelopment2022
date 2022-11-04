.PHONY: clean normal_tests test_base test_open_error_handling test_other_error_handling preload_tests test_with_protected_injection_normal_file test_with_protected_injection_protected_file
CC = cc
CFLAGS = -Wall -Werror -Wextra -O3 -fPIC
GENERATES = move $(TEST_DIR)
SHARED = -shared

PROJECT_DIR = $(shell pwd)
TEST_SRC = $(PROJECT_DIR)/test
TEST_DIR = $(PROJECT_DIR)/test_tmp
IN = $(TEST_SRC)/test.txt
IN_COPY = $(TEST_DIR)/test.txt
IN_PROTECTED = $(TEST_SRC)/testPROTECTED.txt
IN_PROTECTED_COPY = $(TEST_DIR)/testPROTECTED.txt
OUT = $(TEST_DIR)/test-out.txt
EXPECTED = $(TEST_SRC)/expected.txt
EXPECTED_PROTECTED = $(TEST_SRC)/expectedPROTECTED.txt
STRACE_OUT = $(TEST_DIR)/trace.log


move: move.c

preload.so: preload.c
	$(CC) $(CFLAGS) $(SHARED) $^ -o $@

tests: normal_tests preload_tests

normal_tests: test_base test_open_error_handling test_other_error_handling

preload_tests: test_with_protected_injection_normal_file test_with_protected_injection_protected_file

test_base: move test/expected.txt
	@ echo "test_base"

	@ mkdir -p $(TEST_DIR)
	@ cp $(IN) $(IN_COPY)

	@ ./move $(IN_COPY) $(OUT)
	@ cmp $(EXPECTED) $(OUT)
	@if [ -f $(IN_COPY) ]; then exit 1; fi

	@ echo 'test_base passed'

test_open_error_handling: move test
	@ echo "test_open_error_handling"

	@ mkdir -p $(TEST_DIR)
	@ cp $(IN) $(IN_COPY)

	@strace -fo$(STRACE_OUT) -eopenat -e fault=openat:error=ENOENT:when=3 ./move $(IN_COPY) $(OUT) 2>&1 | grep -q "Can not open input file: No such file or directory"
	@if [ ! -f $(IN_COPY) ]; then exit 1; fi;

	@strace -fo$(STRACE_OUT) -eopenat -e fault=openat:error=ENOENT:when=4 ./move $(IN_COPY) $(OUT) 2>&1 | grep -q "Can not open output file: No such file or directory"
	@if [ ! -f $(IN_COPY) ]; then exit 1; fi;

	@ echo 'test_open_error_handling passed'


test_other_error_handling: move test
	@ echo "test_other_error_handling"

	@ mkdir -p $(TEST_DIR)
	@ cp $(IN) $(IN_COPY)

	@strace -fo$(STRACE_OUT) -eread -e fault=read:error=EINVAL:when=2 ./move $(IN_COPY) $(OUT) 2>&1 | grep -q "Error on reading: Invalid argument"
	@if [ ! -f $(IN_COPY) ]; then exit 1; fi;

	@strace -fo$(STRACE_OUT) -e fault=unlink:error=ENOMEM:when=1 ./move $(IN_COPY) $(OUT) 2>&1 | grep -q "Was not able to remove input file: Cannot allocate memory"
	@if [ ! -f $(IN_COPY) ]; then exit 1; fi;

	@ echo 'test_other_error_handling passed'


test_with_protected_injection_normal_file: move preload.so
	@ echo "test_with_protected_injection_normal_file"

	@ mkdir -p $(TEST_DIR)
	@ cp $(IN) $(IN_COPY)

	@LD_PRELOAD=./preload.so ./move $(IN_COPY) $(OUT)
	@if [ -f $(IN_COPY) ]; then exit 1; fi

	@echo "test_with_protected_injection_normal_file passed"

test_with_protected_injection_protected_file: move preload.so
	@ echo "test_with_protected_injection_protected_file"

	@ mkdir -p $(TEST_DIR)
	@ cp $(IN_PROTECTED) $(IN_PROTECTED_COPY)

	@LD_PRELOAD=./preload.so ./move $(IN_PROTECTED_COPY) $(OUT)
	@if [ ! -f $(IN_PROTECTED_COPY) ]; then exit 1; fi

	@echo "test_with_protected_injection_protected_file passed"

clean:
	@ rm -rf $(GENERATES) $(TEST_DIR)