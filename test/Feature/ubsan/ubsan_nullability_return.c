// RUN: %clang %s -fsanitize=nullability-return -emit-llvm -g %O0opt -c -o %t.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out %t.bc 2>&1 | FileCheck %s

#include "klee/klee.h"

int *_Nonnull nonnull_retval(int *p) {
  // CHECK: ubsan_nullability_return.c:[[@LINE+1]]: null pointer returned from function declared to never return null
  return p;
}

int main() {
  _Bool null;

  klee_make_symbolic(&null, sizeof null, "null");

  int local = 0;
  int *arg = null ? 0x0 : &local;

  volatile int *result = nonnull_retval(arg);
  return 0;
}
