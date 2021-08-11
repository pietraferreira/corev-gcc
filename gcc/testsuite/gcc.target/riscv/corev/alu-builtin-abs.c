/* { dg-options "-march=rv32imc_xcorev1p0" } */
/* { dg-do run } */
#include <stdlib.h>

int src1[] = {-2147483648,  -675, 0, 4358, 2147483647};

int
main(void)
{
  if (__builtin_corev_abs(src1[0]) != -2147483648) abort();
  if (__builtin_corev_abs(src1[1]) !=        675) abort();
  if (__builtin_corev_abs(src1[2]) !=          0) abort();
  if (__builtin_corev_abs(src1[3]) !=       4358) abort();
  if (__builtin_corev_abs(src1[4]) != 2147483647) abort();

  return 0;
}
