#include <emscripten.h>
#include <emscripten/html5.h>
#include <stdio.h>
#include "math_utils.hpp"
#include <print>

EM_JS(void, console_log_result, (const char* operation, int result), {
  console.log(UTF8ToString(operation) + " = " + result);
});

static int loop_counter = 0;

// Main loop function for emscripten_set_main_loop
void main_loop() {
  loop_counter++;
  if (loop_counter % 60 == 0) {
    int seconds = loop_counter / 60;
    int fact = factorial(seconds % 10);
    printf("Tick %d: factorial(%d) = %d\n", seconds, seconds % 10, fact);
  }
}

int main(int argc, char* argv[]) {
  int sum = add(10, 25);
  console_log_result("add(10, 25)", sum);

  int product = multiply(7, 8);
  console_log_result("multiply(7, 8)", product);

  int fact5 = factorial(5);
  console_log_result("factorial(5)", fact5);

  EM_ASM({ console.log("Sum from C++: " + $0 + ", Product: " + $1); }, sum,
         product);

  printf("Starting main loop (prints factorial every second)...\n");
  emscripten_set_main_loop(main_loop, 60, 0);

  return 0;
}
