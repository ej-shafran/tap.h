# tap.h

A tiny header-only, [STB](https://github.com/nothings/stb)-style library for
the [Test Anything Protocol](https://testanything.org/).

## Usage

Works like other STB-style libraries - you can see
[here](https://github.com/nothings/stb?tab=readme-ov-file#how-do-i-use-these-libraries).

1. Copy the `tap.h` file to your project. A `bash` one-liner is:

```bash
curl -sSLO https://github.com/ej-shafran/tap.h/raw/main/tap.h
```

2. Define the `TAP_IMPLEMENTATION` macro in the entry point to your
   application/test.

3. `#include` the `tap.h` file.

4. Define tests in a `main` function, and finish it off with a call to
   `tap_end`.

You can see the `tests/example.test.c` file for an example. Broadly:

- Use the `TAP_EXPECT` macro to define expectations
- Use `tap_ok` or `tap_not_ok` to define a test that always succeeds/fails
- Use `TAP_TODO_Q` (or `TAP_TODO` with a message) to mark the next test as an
  expected failure
- Use `TAP_SKIP_Q` (or `TAP_SKIP` with a message) to mark the next test as
  skipped
- Use `tap_log` to print miscellaneous logs

## Automake

Automake has support for the TAP, so it's relatively simple to setup this
library to work with `make check`.

1. Copy Automake's `tap-driver.sh` file. A `bash` one-liner is:

```bash
curl -sSLO https://github.com/ej-shafran/tap.h/raw/main/tap-driver.sh
```

> [!NOTE]
>
> This will copy the version of `tap-driver.sh` from this repository, which may
> be outdated.
>
> To make sure you have the latest version you'll have to copy the file from a
> distribution of Automake.

2. Setup an auxiliary build tools directory in your `configure.ac`, and load
   the `tap-driver.sh` file into it.

```config
AC_CONFIG_AUX_DIR([build-aux])
# Change to the path to the `tap-driver.sh` file from `configure.ac`, if needed
AC_REQUIRE_AUX_FILE([tap-driver.sh])
```

4. Create a `tests` directory, and your tests (which should end in `.test.c`).
   Add a `Makefile.am` with:

```automake
TEST_LOG_DRIVER = env AM_TMP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/build-aux/tap-driver.sh

# To print out `tap_log` messages when running `make check`
TEST_LOG_DRIVER_FLAGS = --comments

# Fill in your tests
TESTS = foo.test
check_PROGRAMS = foo.test

# And change the path to `tap.h` if it's somewhere else
foo_test_SOURCES = foo.test.c $(top_srcdir)/tap.h
```

4. Reconfigure (`autoreconf -vi && ./configure`).

5. Run `make check`.

## Other harnesses

Any TAP harness should work. A simple one is
[`tapview`](http://www.catb.org/~esr/tapview/tapview.html), which you can use
to run a compiled file that uses `tap.h` like so:

```bash
./foo | ./tapview
```

A `bash` one-liner to copy the `tapview` file:

```bash
curl -sSL 'https://gitlab.com/esr/tapview/-/raw/master/tapview?ref_type=heads&inline=false' -o tapview && chmod u+x tapview
```
