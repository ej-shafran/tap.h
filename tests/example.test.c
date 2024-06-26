#include <stdbool.h>
#define TAP_IMPLEMENTATION
#include "../tap.h"

int main(void)
{
	TAP_EXPECT(true, "an expectation will fail if passed a false value...");

	TAP_TODO("fails")
	TAP_EXPECT(false, "...but can be marked as intentionally failing...");

	TAP_SKIP("don't run")
	TAP_EXPECT(true, "...or skipped altogether");

	tap_ok("you can use `tap_ok` to specify that a test is passing...");
	TAP_TODO("fails")
	tap_not_ok("...or `tap_not_ok` to specify that it failed");

	tap_log("`tap_log` will log out arbitrary information");

	tap_log("you can specify a test is ok without a message...");
	tap_ok_q();

	tap_log("...or that it isn't ok, or TODO...");
	TAP_TODO_Q tap_not_ok_q();

	tap_log("...or skipped...");
	TAP_SKIP_Q tap_ok_q();

	tap_log("...and you can define expectations without a failure message");
	TAP_EXPECT_Q(true);

	tap_log("note that all non-q functions are %s-like", "printf");

	tap_end();
}
