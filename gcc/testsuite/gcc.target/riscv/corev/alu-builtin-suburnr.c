/* { dg-options "-march=rv32imc_xcorev1p0" } */
/* { dg-do run } */
#include <stdlib.h>

int dest[] = {-2147483648,  -30, 0, 3489, 2147483647};
int src1[] = {-2147483648,  -675, 0, 4358, 2147483647};
int src2[] = {3, 23, 0, 12, 31};

int
main(void)
{
  if (__builtin_corev_suburnr(dest[0], src1[2], src2[0]) != 268435456) abort();
  if (__builtin_corev_suburnr(dest[0], src1[0], src2[2]) != 0) abort();
  if (__builtin_corev_suburnr(dest[0], src1[1], src2[4]) != 1) abort();

  if (__builtin_corev_suburnr(dest[1], src1[2], src2[1]) != 0) abort();
  if (__builtin_corev_suburnr(dest[1], src1[3], src2[2]) != -4388) abort();
  if (__builtin_corev_suburnr(dest[1], src1[4], src2[3]) != 524288) abort();

  if (__builtin_corev_suburnr(dest[2], src1[4], src2[0]) != 268435456) abort();
  if (__builtin_corev_suburnr(dest[2], src1[2], src2[2]) != 0) abort();
  if (__builtin_corev_suburnr(dest[2], src1[3], src2[4]) != 0) abort();

  if (__builtin_corev_suburnr(dest[3], src1[3], src2[1]) != 0) abort();
  if (__builtin_corev_suburnr(dest[3], src1[4], src2[2]) != -2147480158) abort();
  if (__builtin_corev_suburnr(dest[3], src1[0], src2[3]) != 524289) abort();

  if (__builtin_corev_suburnr(dest[4], src1[2], src2[1]) != 256) abort();
  if (__builtin_corev_suburnr(dest[4], src1[0], src2[3]) != 0) abort();
  if (__builtin_corev_suburnr(dest[4], src1[4], src2[4]) != 0) abort();

  return 0;
}
