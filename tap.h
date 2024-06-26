#ifndef TAP_H_
#define TAP_H_

#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>

#if defined(__GNUC__) || defined(__clang__)
#define PRINTF_LIKE(arg, start) __attribute__((format(printf, arg, start)))
#else
#define PRINTF_LIKE(...)
#endif // __GNUC__ || __clang__

void tap_plan(int n);
void tap_end(void);

PRINTF_LIKE(1, 2) void tap_log(const char *fmt, ...);

void tap_ok_q(void);
PRINTF_LIKE(1, 2) void tap_ok(const char *fmt, ...);

void tap_not_ok_q(void);
PRINTF_LIKE(1, 2) void tap_not_ok(const char *fmt, ...);

void tap_bail_out_q(void);
PRINTF_LIKE(1, 2) void tap_bail_out(const char *fmt, ...);

#define TAP_TODO(msg)            \
	do {                     \
		tap__todo = msg; \
	} while (0);

#define TAP_TODO_Q TAP_TODO("")

#define TAP_SKIP(msg)            \
	do {                     \
		tap__skip = msg; \
	} while (0);

#define TAP_SKIP_Q TAP_SKIP("")

#define TAP_EXPECT_Q(condition)         \
	do {                            \
		if (condition) {        \
			tap_ok_q();     \
		} else {                \
			tap_not_ok_q(); \
		}                       \
	} while (0)

#define TAP_EXPECT(condition, ...)               \
	do {                                     \
		if (condition) {                 \
			tap_ok(__VA_ARGS__);     \
		} else {                         \
			tap_not_ok(__VA_ARGS__); \
		}                                \
	} while (0)

static int tap__plan = 0;
static const char *tap__todo = NULL;
static const char *tap__skip = NULL;
static void tap__print_extras(void)
{
	if (tap__todo) {
		printf(" # TODO");
		if (tap__todo[0] != '\0')
			printf(" %s", tap__todo);
		tap__todo = NULL;
	} else if (tap__skip) {
		printf(" # SKIP");
		if (tap__skip[0] != '\0')
			printf(" %s", tap__skip);
		tap__skip = NULL;
	}
}

#ifdef TAP_IMPLEMENTATION

void tap_plan(int n)
{
	printf("1..%d\n", n);
}

void tap_end(void)
{
	printf("1..%d\n", tap__plan);
}

PRINTF_LIKE(1, 2) void tap_log(const char *fmt, ...)
{
	printf("# ");

	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	printf("\n");
}

void tap_ok_q(void)
{
	tap__plan += 1;

	printf("ok");
	tap__print_extras();
	printf("\n");
}

PRINTF_LIKE(1, 2) void tap_ok(const char *fmt, ...)
{
	tap__plan += 1;

	printf("ok - ");

	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	tap__print_extras();

	printf("\n");
}

void tap_not_ok_q(void)
{
	tap__plan += 1;

	printf("not ok");

	tap__print_extras();

	printf("\n");
}

PRINTF_LIKE(1, 2) void tap_not_ok(const char *fmt, ...)
{
	tap__plan += 1;

	printf("not ok - ");

	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	tap__print_extras();

	printf("\n");
}

void tap_bail_out_q(void)
{
	printf("Bail out!\n");
}

PRINTF_LIKE(1, 2) void tap_bail_out(const char *fmt, ...)
{
	printf("Bail out!");

	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	printf("\n");
}

#endif // TAP_IMPLEMENTATION

#endif // TAP_H_
