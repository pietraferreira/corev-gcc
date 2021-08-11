/* { dg-options "-march=rv32imc_xcorev1p0" } */
/* { dg-do run } */
#include <stdlib.h>

int src1[] = {0, 39, 758, 4358, 2147483647};
int src2[] = {0, 46, 547, 4358, 2147483647};

int
main(void)
{
  if (__builtin_corev_minu(src1[0], src2[1]) != 0) abort();
  if (__builtin_corev_minu(src1[0], src2[2]) != 0) abort();
  if (__builtin_corev_minu(src1[0], src2[4]) != 0) abort();

  if (__builtin_corev_minu(src1[1], src2[4]) != 39) abort();
  if (__builtin_corev_minu(src1[1], src2[2]) != 39) abort();
  if (__builtin_corev_minu(src1[1], src2[3]) != 39) abort();

  if (__builtin_corev_minu(src1[2], src2[3]) != 758) abort();
  if (__builtin_corev_minu(src1[2], src2[0]) != 0) abort();
  if (__builtin_corev_minu(src1[2], src2[4]) != 758) abort();

  if (__builtin_corev_minu(src1[3], src2[0]) !=  0) abort();
  if (__builtin_corev_minu(src1[3], src2[2]) !=  547) abort();
  if (__builtin_corev_minu(src1[3], src2[1]) !=  46) abort();

  if (__builtin_corev_minu(src1[4], src2[2]) !=  547) abort();
  if (__builtin_corev_minu(src1[4], src2[1]) !=  46) abort();
  if (__builtin_corev_minu(src1[4], src2[3]) !=  4358) abort();

  return 0;
}
