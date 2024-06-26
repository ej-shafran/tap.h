TEST_LOG_DRIVER = env AM_TMP_AWK='$(AWK)' $(SHELL) \
		  $(top_srcdir)/build-aux/tap-driver.sh

# Prints out `tap_log` messages when running `make check`
TEST_LOG_DRIVER_FLAGS = --comments

TESTS = example.test
check_PROGRAMS = example.test

example_test_SOURCES = example.test.c $(top_srcdir)/tap.h
