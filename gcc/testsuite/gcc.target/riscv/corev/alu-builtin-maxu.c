/* { dg-options "-march=rv32imc_xcorev1p0" } */
/* { dg-do run } */
#include <stdlib.h>

int src1[] = {0, 39, 758, 4358, 2147483647};
int src2[] = {0, 46, 547, 4358, 2147483647};

int
main(void)
{
  if (__builtin_corev_maxu(src1[0], src2[1]) != 46) abort();
  if (__builtin_corev_maxu(src1[0], src2[2]) != 547) abort();
  if (__builtin_corev_maxu(src1[0], src2[4]) != 2147483647) abort();

  if (__builtin_corev_maxu(src1[1], src2[4]) != 2147483647) abort();
  if (__builtin_corev_maxu(src1[1], src2[2]) != 547) abort();
  if (__builtin_corev_maxu(src1[1], src2[3]) != 4358) abort();

  if (__builtin_corev_maxu(src1[2], src2[3]) != 4358) abort();
  if (__builtin_corev_maxu(src1[2], src2[0]) != 758) abort();
  if (__builtin_corev_maxu(src1[2], src2[4]) != 2147483647) abort();

  if (__builtin_corev_maxu(src1[3], src2[0]) !=  4358) abort();
  if (__builtin_corev_maxu(src1[3], src2[2]) !=  4358) abort();
  if (__builtin_corev_maxu(src1[3], src2[1]) !=  4358) abort();

  if (__builtin_corev_maxu(src1[4], src2[2]) !=  2147483647) abort();
  if (__builtin_corev_maxu(src1[4], src2[1]) !=  2147483647) abort();
  if (__builtin_corev_maxu(src1[4], src2[3]) !=  2147483647) abort();

  return 0;
}
