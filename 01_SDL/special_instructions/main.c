#include <stdlib.h>

// bitcast with -O1
float bitcast(unsigned int x) {
  union {
    unsigned int i;
    float f;
  } u;
  return u.i = x, u.f;
}

// tail call with -O1
int some_function(int x);
int wrapper(int x) { return some_function(x); }

int main() {
  // trunc with -O0
  int int_trunc;
  char char_trunc = (char)int_trunc;

  // getelementptr with -O0
  int arr[1];
  int num = arr[0];

  // srem with -O0
  int a_srem, b_srem;
  int srem = a_srem % b_srem;

  // lshr with -O0
  size_t a_lshr = 16, b_lshr = 2;
  size_t lshr = a_lshr >> b_lshr;

  // sitofp with -O0
  int int_sitofp;
  float float_sitofp = (float)int_sitofp;

  // zext and select with -O0
  int int_select;
  int select = int_select ? 0 : 1;

  // fpext with -O0
  float x;
  double y = x;
}
