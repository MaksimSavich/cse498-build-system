#include "math_utils.hpp"

#include <emscripten.h>

extern "C" {

EMSCRIPTEN_KEEPALIVE
int add(int x, int y) { return x + y; }

EMSCRIPTEN_KEEPALIVE
int multiply(int x, int y) { return x * y; }

EMSCRIPTEN_KEEPALIVE
int factorial(int x) {
  if (x <= 1) return 1;
  return x * factorial(x - 1);
}
}
