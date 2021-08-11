/* { dg-options "-march=rv32imc_xcorev1p0" } */
/* { dg-do run } */
#include <stdlib.h>

int src1[] = {-2147483648,  -675, 0, 4358, 2147483647};
int src2[] = {-2147483648,  -675, 0, 4358, 2147483647};

int
main(void)
{
  if (__builtin_corev_min(src1[0], src2[1]) != -2147483648) abort();
  if (__builtin_corev_min(src1[0], src2[2]) != -2147483648) abort();
  if (__builtin_corev_min(src1[0], src2[4]) != -2147483648) abort();

  if (__builtin_corev_min(src1[1], src2[4]) != -675) abort();
  if (__builtin_corev_min(src1[1], src2[2]) != -675) abort();
  if (__builtin_corev_min(src1[1], src2[3]) != -675) abort();

  if (__builtin_corev_min(src1[2], src2[3]) != 0) abort();
  if (__builtin_corev_min(src1[2], src2[0]) != -2147483648) abort();
  if (__builtin_corev_min(src1[2], src2[4]) != 0) abort();

  if (__builtin_corev_min(src1[3], src2[0]) != -2147483648) abort();
  if (__builtin_corev_min(src1[3], src2[2]) != 0) abort();
  if (__builtin_corev_min(src1[3], src2[1]) != -675) abort();

  if (__builtin_corev_min(src1[4], src2[2]) != 0) abort();
  if (__builtin_corev_min(src1[4], src2[1]) != -675) abort();
  if (__builtin_corev_min(src1[4], src2[3]) != 4358) abort();

  return 0;
}
