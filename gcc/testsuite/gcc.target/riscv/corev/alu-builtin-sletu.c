/* { dg-options "-march=rv32imc_xcorev1p0" } */
/* { dg-do run } */
#include <stdlib.h>

int src1[] = {-2147483648,  -675, 0, 4358, 2147483647};
int src2[] = {-2147483648,  -675, 0, 4358, 2147483647};

int
main(void)
{
  if (__builtin_corev_sletu(src1[0], src2[0]) != 1) abort();
  if (__builtin_corev_sletu(src1[0], src2[1]) != 1) abort();
  if (__builtin_corev_sletu(src1[0], src2[4]) != 1) abort();

  if (__builtin_corev_sletu(src1[1], src2[1]) != 1) abort();
  if (__builtin_corev_sletu(src1[1], src2[2]) != 1) abort();
  if (__builtin_corev_sletu(src1[1], src2[3]) != 1) abort();

  if (__builtin_corev_sletu(src1[2], src2[0]) != 0) abort();
  if (__builtin_corev_sletu(src1[2], src2[2]) != 1) abort();
  if (__builtin_corev_sletu(src1[2], src2[4]) != 1) abort();

  if (__builtin_corev_sletu(src1[3], src2[1]) != 0) abort();
  if (__builtin_corev_sletu(src1[3], src2[2]) != 0) abort();
  if (__builtin_corev_sletu(src1[3], src2[3]) != 1) abort();

  if (__builtin_corev_sletu(src1[4], src2[1]) != 0) abort();
  if (__builtin_corev_sletu(src1[4], src2[3]) != 0) abort();
  if (__builtin_corev_sletu(src1[4], src2[4]) != 1) abort();

  return 0;
}
